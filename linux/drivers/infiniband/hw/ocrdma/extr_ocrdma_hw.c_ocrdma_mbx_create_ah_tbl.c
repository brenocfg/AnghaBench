#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocrdma_pbe {void* pa_hi; void* pa_lo; } ;
struct ocrdma_mqe {int dummy; } ;
struct TYPE_7__ {int pa; int /*<<< orphan*/ * va; } ;
struct TYPE_8__ {int size; int pa; int num_ah; int ahid; TYPE_3__ pbl; int /*<<< orphan*/ * va; } ;
struct TYPE_5__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_4__ av_tbl; TYPE_1__ nic_info; } ;
struct ocrdma_create_ah_tbl_rsp {int ahid; } ;
struct ocrdma_create_ah_tbl {int ah_conf; TYPE_2__* tbl_addr; } ;
struct ocrdma_av {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {void* hi; void* lo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OCRDMA_AH_TBL_PAGES ; 
 int /*<<< orphan*/  OCRDMA_CMD_CREATE_AH_TBL ; 
 int OCRDMA_CREATE_AH_ENTRY_SIZE_MASK ; 
 int OCRDMA_CREATE_AH_ENTRY_SIZE_SHIFT ; 
 int OCRDMA_CREATE_AH_NUM_PAGES_MASK ; 
 int OCRDMA_CREATE_AH_NUM_PAGES_SHIFT ; 
 int OCRDMA_CREATE_AH_PAGE_SIZE_MASK ; 
 int OCRDMA_CREATE_AH_PAGE_SIZE_SHIFT ; 
 int OCRDMA_MAX_AH ; 
 int OCRDMA_MAX_Q_PAGE_SIZE_CNT ; 
 int OCRDMA_MIN_Q_PAGE_SIZE ; 
 int PAGE_SIZE ; 
 scalar_t__ cpu_to_le32 (int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_create_ah_tbl*) ; 
 struct ocrdma_create_ah_tbl* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int ocrdma_mbx_create_ah_tbl(struct ocrdma_dev *dev)
{
	int i;
	int status = -ENOMEM;
	int max_ah;
	struct ocrdma_create_ah_tbl *cmd;
	struct ocrdma_create_ah_tbl_rsp *rsp;
	struct pci_dev *pdev = dev->nic_info.pdev;
	dma_addr_t pa;
	struct ocrdma_pbe *pbes;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_CREATE_AH_TBL, sizeof(*cmd));
	if (!cmd)
		return status;

	max_ah = OCRDMA_MAX_AH;
	dev->av_tbl.size = sizeof(struct ocrdma_av) * max_ah;

	/* number of PBEs in PBL */
	cmd->ah_conf = (OCRDMA_AH_TBL_PAGES <<
				OCRDMA_CREATE_AH_NUM_PAGES_SHIFT) &
				OCRDMA_CREATE_AH_NUM_PAGES_MASK;

	/* page size */
	for (i = 0; i < OCRDMA_MAX_Q_PAGE_SIZE_CNT; i++) {
		if (PAGE_SIZE == (OCRDMA_MIN_Q_PAGE_SIZE << i))
			break;
	}
	cmd->ah_conf |= (i << OCRDMA_CREATE_AH_PAGE_SIZE_SHIFT) &
				OCRDMA_CREATE_AH_PAGE_SIZE_MASK;

	/* ah_entry size */
	cmd->ah_conf |= (sizeof(struct ocrdma_av) <<
				OCRDMA_CREATE_AH_ENTRY_SIZE_SHIFT) &
				OCRDMA_CREATE_AH_ENTRY_SIZE_MASK;

	dev->av_tbl.pbl.va = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
						&dev->av_tbl.pbl.pa,
						GFP_KERNEL);
	if (dev->av_tbl.pbl.va == NULL)
		goto mem_err;

	dev->av_tbl.va = dma_alloc_coherent(&pdev->dev, dev->av_tbl.size,
					    &pa, GFP_KERNEL);
	if (dev->av_tbl.va == NULL)
		goto mem_err_ah;
	dev->av_tbl.pa = pa;
	dev->av_tbl.num_ah = max_ah;

	pbes = (struct ocrdma_pbe *)dev->av_tbl.pbl.va;
	for (i = 0; i < dev->av_tbl.size / OCRDMA_MIN_Q_PAGE_SIZE; i++) {
		pbes[i].pa_lo = (u32)cpu_to_le32(pa & 0xffffffff);
		pbes[i].pa_hi = (u32)cpu_to_le32(upper_32_bits(pa));
		pa += PAGE_SIZE;
	}
	cmd->tbl_addr[0].lo = (u32)(dev->av_tbl.pbl.pa & 0xFFFFFFFF);
	cmd->tbl_addr[0].hi = (u32)upper_32_bits(dev->av_tbl.pbl.pa);
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;
	rsp = (struct ocrdma_create_ah_tbl_rsp *)cmd;
	dev->av_tbl.ahid = rsp->ahid & 0xFFFF;
	kfree(cmd);
	return 0;

mbx_err:
	dma_free_coherent(&pdev->dev, dev->av_tbl.size, dev->av_tbl.va,
			  dev->av_tbl.pa);
	dev->av_tbl.va = NULL;
mem_err_ah:
	dma_free_coherent(&pdev->dev, PAGE_SIZE, dev->av_tbl.pbl.va,
			  dev->av_tbl.pbl.pa);
	dev->av_tbl.pbl.va = NULL;
	dev->av_tbl.size = 0;
mem_err:
	kfree(cmd);
	return status;
}