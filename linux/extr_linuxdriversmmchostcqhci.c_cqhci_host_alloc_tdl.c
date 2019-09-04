#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cqhci_host {int caps; int task_desc_len; int quirks; int trans_desc_len; int link_desc_len; int slot_sz; int desc_size; int num_slots; int data_size; scalar_t__ trans_desc_dma_base; scalar_t__ desc_dma_base; void* trans_desc_base; int /*<<< orphan*/ * desc_base; TYPE_1__* mmc; scalar_t__ dma64; } ;
struct TYPE_3__ {int max_segs; int cqe_qdepth; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_CFG ; 
 int CQHCI_QUIRK_SHORT_TXFR_DESC_SZ ; 
 int CQHCI_TASK_DESC_SZ ; 
 int CQHCI_TASK_DESC_SZ_128 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cqhci_readl (struct cqhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqhci_writel (struct cqhci_host*,int,int /*<<< orphan*/ ) ; 
 void* dmam_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,unsigned long long,...) ; 
 int /*<<< orphan*/  setup_trans_desc (struct cqhci_host*,int) ; 

__attribute__((used)) static int cqhci_host_alloc_tdl(struct cqhci_host *cq_host)
{
	int i = 0;

	/* task descriptor can be 64/128 bit irrespective of arch */
	if (cq_host->caps & CQHCI_TASK_DESC_SZ_128) {
		cqhci_writel(cq_host, cqhci_readl(cq_host, CQHCI_CFG) |
			       CQHCI_TASK_DESC_SZ, CQHCI_CFG);
		cq_host->task_desc_len = 16;
	} else {
		cq_host->task_desc_len = 8;
	}

	/*
	 * 96 bits length of transfer desc instead of 128 bits which means
	 * ADMA would expect next valid descriptor at the 96th bit
	 * or 128th bit
	 */
	if (cq_host->dma64) {
		if (cq_host->quirks & CQHCI_QUIRK_SHORT_TXFR_DESC_SZ)
			cq_host->trans_desc_len = 12;
		else
			cq_host->trans_desc_len = 16;
		cq_host->link_desc_len = 16;
	} else {
		cq_host->trans_desc_len = 8;
		cq_host->link_desc_len = 8;
	}

	/* total size of a slot: 1 task & 1 transfer (link) */
	cq_host->slot_sz = cq_host->task_desc_len + cq_host->link_desc_len;

	cq_host->desc_size = cq_host->slot_sz * cq_host->num_slots;

	cq_host->data_size = cq_host->trans_desc_len * cq_host->mmc->max_segs *
		cq_host->mmc->cqe_qdepth;

	pr_debug("%s: cqhci: desc_size: %zu data_sz: %zu slot-sz: %d\n",
		 mmc_hostname(cq_host->mmc), cq_host->desc_size, cq_host->data_size,
		 cq_host->slot_sz);

	/*
	 * allocate a dma-mapped chunk of memory for the descriptors
	 * allocate a dma-mapped chunk of memory for link descriptors
	 * setup each link-desc memory offset per slot-number to
	 * the descriptor table.
	 */
	cq_host->desc_base = dmam_alloc_coherent(mmc_dev(cq_host->mmc),
						 cq_host->desc_size,
						 &cq_host->desc_dma_base,
						 GFP_KERNEL);
	if (!cq_host->desc_base)
		return -ENOMEM;

	cq_host->trans_desc_base = dmam_alloc_coherent(mmc_dev(cq_host->mmc),
					      cq_host->data_size,
					      &cq_host->trans_desc_dma_base,
					      GFP_KERNEL);
	if (!cq_host->trans_desc_base) {
		dmam_free_coherent(mmc_dev(cq_host->mmc), cq_host->desc_size,
				   cq_host->desc_base,
				   cq_host->desc_dma_base);
		cq_host->desc_base = NULL;
		cq_host->desc_dma_base = 0;
		return -ENOMEM;
	}

	pr_debug("%s: cqhci: desc-base: 0x%p trans-base: 0x%p\n desc_dma 0x%llx trans_dma: 0x%llx\n",
		 mmc_hostname(cq_host->mmc), cq_host->desc_base, cq_host->trans_desc_base,
		(unsigned long long)cq_host->desc_dma_base,
		(unsigned long long)cq_host->trans_desc_dma_base);

	for (; i < (cq_host->num_slots); i++)
		setup_trans_desc(cq_host, i);

	return 0;
}