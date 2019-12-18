#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct wmi_pmc_cmd {int /*<<< orphan*/  mem_base; void* ring_size; int /*<<< orphan*/  op; int /*<<< orphan*/  member_0; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct pmc_ctx {int num_descriptors; int descriptor_size; int last_cmd_status; int /*<<< orphan*/  lock; TYPE_3__* descriptors; struct vring_tx_desc* pring_va; int /*<<< orphan*/  pring_pa; } ;
struct wil6210_priv {int dma_addr_size; int /*<<< orphan*/  main_ndev; struct pmc_ctx pmc; } ;
struct TYPE_5__ {void* addr_high; int /*<<< orphan*/  addr_low; } ;
struct TYPE_6__ {int d0; void* length; scalar_t__ status; TYPE_1__ addr; } ;
struct vring_tx_desc {TYPE_2__ dma; } ;
struct device {int dummy; } ;
struct desc_alloc_info {int dummy; } ;
typedef  int /*<<< orphan*/  pmc_cmd ;
struct TYPE_7__ {struct vring_tx_desc* va; int /*<<< orphan*/  pa; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_MAX ; 
 int PCM_DATA_INVALID_DW_VAL ; 
 int RX_DMA_D0_CMD_DMA_IT ; 
 int WIL_RING_SIZE_ORDER_MAX ; 
 int /*<<< orphan*/  WMI_PMC_ALLOCATE ; 
 int /*<<< orphan*/  WMI_PMC_CMDID ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,struct vring_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 TYPE_3__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* ndev_to_vif (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 scalar_t__ wil_is_pmc_allocated (struct pmc_ctx*) ; 
 struct device* wil_to_dev (struct wil6210_priv*) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_pmc_cmd*,int) ; 

void wil_pmc_alloc(struct wil6210_priv *wil,
		   int num_descriptors,
		   int descriptor_size)
{
	u32 i;
	struct pmc_ctx *pmc = &wil->pmc;
	struct device *dev = wil_to_dev(wil);
	struct wil6210_vif *vif = ndev_to_vif(wil->main_ndev);
	struct wmi_pmc_cmd pmc_cmd = {0};
	int last_cmd_err = -ENOMEM;

	mutex_lock(&pmc->lock);

	if (wil_is_pmc_allocated(pmc)) {
		/* sanity check */
		wil_err(wil, "ERROR pmc is already allocated\n");
		goto no_release_err;
	}
	if ((num_descriptors <= 0) || (descriptor_size <= 0)) {
		wil_err(wil,
			"Invalid params num_descriptors(%d), descriptor_size(%d)\n",
			num_descriptors, descriptor_size);
		last_cmd_err = -EINVAL;
		goto no_release_err;
	}

	if (num_descriptors > (1 << WIL_RING_SIZE_ORDER_MAX)) {
		wil_err(wil,
			"num_descriptors(%d) exceeds max ring size %d\n",
			num_descriptors, 1 << WIL_RING_SIZE_ORDER_MAX);
		last_cmd_err = -EINVAL;
		goto no_release_err;
	}

	if (num_descriptors > INT_MAX / descriptor_size) {
		wil_err(wil,
			"Overflow in num_descriptors(%d)*descriptor_size(%d)\n",
			num_descriptors, descriptor_size);
		last_cmd_err = -EINVAL;
		goto no_release_err;
	}

	pmc->num_descriptors = num_descriptors;
	pmc->descriptor_size = descriptor_size;

	wil_dbg_misc(wil, "pmc_alloc: %d descriptors x %d bytes each\n",
		     num_descriptors, descriptor_size);

	/* allocate descriptors info list in pmc context*/
	pmc->descriptors = kcalloc(num_descriptors,
				  sizeof(struct desc_alloc_info),
				  GFP_KERNEL);
	if (!pmc->descriptors) {
		wil_err(wil, "ERROR allocating pmc skb list\n");
		goto no_release_err;
	}

	wil_dbg_misc(wil, "pmc_alloc: allocated descriptors info list %p\n",
		     pmc->descriptors);

	/* Allocate pring buffer and descriptors.
	 * vring->va should be aligned on its size rounded up to power of 2
	 * This is granted by the dma_alloc_coherent.
	 *
	 * HW has limitation that all vrings addresses must share the same
	 * upper 16 msb bits part of 48 bits address. To workaround that,
	 * if we are using more than 32 bit addresses switch to 32 bit
	 * allocation before allocating vring memory.
	 *
	 * There's no check for the return value of dma_set_mask_and_coherent,
	 * since we assume if we were able to set the mask during
	 * initialization in this system it will not fail if we set it again
	 */
	if (wil->dma_addr_size > 32)
		dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));

	pmc->pring_va = dma_alloc_coherent(dev,
			sizeof(struct vring_tx_desc) * num_descriptors,
			&pmc->pring_pa,
			GFP_KERNEL);

	if (wil->dma_addr_size > 32)
		dma_set_mask_and_coherent(dev,
					  DMA_BIT_MASK(wil->dma_addr_size));

	wil_dbg_misc(wil,
		     "pmc_alloc: allocated pring %p => %pad. %zd x %d = total %zd bytes\n",
		     pmc->pring_va, &pmc->pring_pa,
		     sizeof(struct vring_tx_desc),
		     num_descriptors,
		     sizeof(struct vring_tx_desc) * num_descriptors);

	if (!pmc->pring_va) {
		wil_err(wil, "ERROR allocating pmc pring\n");
		goto release_pmc_skb_list;
	}

	/* initially, all descriptors are SW owned
	 * For Tx, Rx, and PMC, ownership bit is at the same location, thus
	 * we can use any
	 */
	for (i = 0; i < num_descriptors; i++) {
		struct vring_tx_desc *_d = &pmc->pring_va[i];
		struct vring_tx_desc dd = {}, *d = &dd;
		int j = 0;

		pmc->descriptors[i].va = dma_alloc_coherent(dev,
			descriptor_size,
			&pmc->descriptors[i].pa,
			GFP_KERNEL);

		if (unlikely(!pmc->descriptors[i].va)) {
			wil_err(wil, "ERROR allocating pmc descriptor %d", i);
			goto release_pmc_skbs;
		}

		for (j = 0; j < descriptor_size / sizeof(u32); j++) {
			u32 *p = (u32 *)pmc->descriptors[i].va + j;
			*p = PCM_DATA_INVALID_DW_VAL | j;
		}

		/* configure dma descriptor */
		d->dma.addr.addr_low =
			cpu_to_le32(lower_32_bits(pmc->descriptors[i].pa));
		d->dma.addr.addr_high =
			cpu_to_le16((u16)upper_32_bits(pmc->descriptors[i].pa));
		d->dma.status = 0; /* 0 = HW_OWNED */
		d->dma.length = cpu_to_le16(descriptor_size);
		d->dma.d0 = BIT(9) | RX_DMA_D0_CMD_DMA_IT;
		*_d = *d;
	}

	wil_dbg_misc(wil, "pmc_alloc: allocated successfully\n");

	pmc_cmd.op = WMI_PMC_ALLOCATE;
	pmc_cmd.ring_size = cpu_to_le16(pmc->num_descriptors);
	pmc_cmd.mem_base = cpu_to_le64(pmc->pring_pa);

	wil_dbg_misc(wil, "pmc_alloc: send WMI_PMC_CMD with ALLOCATE op\n");
	pmc->last_cmd_status = wmi_send(wil,
					WMI_PMC_CMDID,
					vif->mid,
					&pmc_cmd,
					sizeof(pmc_cmd));
	if (pmc->last_cmd_status) {
		wil_err(wil,
			"WMI_PMC_CMD with ALLOCATE op failed with status %d",
			pmc->last_cmd_status);
		goto release_pmc_skbs;
	}

	mutex_unlock(&pmc->lock);

	return;

release_pmc_skbs:
	wil_err(wil, "exit on error: Releasing skbs...\n");
	for (i = 0; i < num_descriptors && pmc->descriptors[i].va; i++) {
		dma_free_coherent(dev,
				  descriptor_size,
				  pmc->descriptors[i].va,
				  pmc->descriptors[i].pa);

		pmc->descriptors[i].va = NULL;
	}
	wil_err(wil, "exit on error: Releasing pring...\n");

	dma_free_coherent(dev,
			  sizeof(struct vring_tx_desc) * num_descriptors,
			  pmc->pring_va,
			  pmc->pring_pa);

	pmc->pring_va = NULL;

release_pmc_skb_list:
	wil_err(wil, "exit on error: Releasing descriptors info list...\n");
	kfree(pmc->descriptors);
	pmc->descriptors = NULL;

no_release_err:
	pmc->last_cmd_status = last_cmd_err;
	mutex_unlock(&pmc->lock);
}