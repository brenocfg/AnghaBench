#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_13__ {int word1; scalar_t__ avail_vpd_len; int /*<<< orphan*/  vpd_paddr_low; int /*<<< orphan*/  vpd_paddr_high; } ;
struct TYPE_10__ {TYPE_8__ read_rev; } ;
struct lpfc_mqe {TYPE_2__ un; } ;
struct lpfc_hba {TYPE_3__* pcidev; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_9__ {struct lpfc_mqe mqe; } ;
struct TYPE_12__ {TYPE_1__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_rd_rev_avail_len ; 
 int /*<<< orphan*/  lpfc_mbx_rd_rev_vpd ; 
 int /*<<< orphan*/  lpfc_read_rev (struct lpfc_hba*,TYPE_4__*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  putPaddrHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putPaddrLow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli4_read_rev(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq,
		    uint8_t *vpd, uint32_t *vpd_size)
{
	int rc = 0;
	uint32_t dma_size;
	struct lpfc_dmabuf *dmabuf;
	struct lpfc_mqe *mqe;

	dmabuf = kzalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
	if (!dmabuf)
		return -ENOMEM;

	/*
	 * Get a DMA buffer for the vpd data resulting from the READ_REV
	 * mailbox command.
	 */
	dma_size = *vpd_size;
	dmabuf->virt = dma_alloc_coherent(&phba->pcidev->dev, dma_size,
					  &dmabuf->phys, GFP_KERNEL);
	if (!dmabuf->virt) {
		kfree(dmabuf);
		return -ENOMEM;
	}

	/*
	 * The SLI4 implementation of READ_REV conflicts at word1,
	 * bits 31:16 and SLI4 adds vpd functionality not present
	 * in SLI3.  This code corrects the conflicts.
	 */
	lpfc_read_rev(phba, mboxq);
	mqe = &mboxq->u.mqe;
	mqe->un.read_rev.vpd_paddr_high = putPaddrHigh(dmabuf->phys);
	mqe->un.read_rev.vpd_paddr_low = putPaddrLow(dmabuf->phys);
	mqe->un.read_rev.word1 &= 0x0000FFFF;
	bf_set(lpfc_mbx_rd_rev_vpd, &mqe->un.read_rev, 1);
	bf_set(lpfc_mbx_rd_rev_avail_len, &mqe->un.read_rev, dma_size);

	rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_POLL);
	if (rc) {
		dma_free_coherent(&phba->pcidev->dev, dma_size,
				  dmabuf->virt, dmabuf->phys);
		kfree(dmabuf);
		return -EIO;
	}

	/*
	 * The available vpd length cannot be bigger than the
	 * DMA buffer passed to the port.  Catch the less than
	 * case and update the caller's size.
	 */
	if (mqe->un.read_rev.avail_vpd_len < *vpd_size)
		*vpd_size = mqe->un.read_rev.avail_vpd_len;

	memcpy(vpd, dmabuf->virt, *vpd_size);

	dma_free_coherent(&phba->pcidev->dev, dma_size,
			  dmabuf->virt, dmabuf->phys);
	kfree(dmabuf);
	return 0;
}