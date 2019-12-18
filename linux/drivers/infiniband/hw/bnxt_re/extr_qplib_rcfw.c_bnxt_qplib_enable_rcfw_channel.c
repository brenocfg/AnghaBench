#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct cmdq_init {void* creq_ring_id; void* cmdq_size_cmdq_lvl; int /*<<< orphan*/  cmdq_pbl; } ;
struct TYPE_6__ {int level; TYPE_2__* pbl; } ;
struct bnxt_qplib_rcfw {int cmdq_depth; int bmap_size; int cmdq_bar_reg; int creq_bar_reg; int (* aeq_handler ) (struct bnxt_qplib_rcfw*,void*,void*) ;int creq_ring_id; int /*<<< orphan*/ * cmdq_bar_reg_iomem; TYPE_3__ cmdq; TYPE_1__* pdev; int /*<<< orphan*/  waitq; scalar_t__ creq_func_event_processed; scalar_t__ creq_qp_event_processed; void* creq_bar_reg_iomem; int /*<<< orphan*/  cmdq_bar_reg_trig_off; int /*<<< orphan*/  cmdq_bar_reg_prod_off; int /*<<< orphan*/  cmdq_bitmap; int /*<<< orphan*/  flags; scalar_t__ seq_num; } ;
typedef  scalar_t__ resource_size_t ;
typedef  int /*<<< orphan*/  init ;
struct TYPE_5__ {int /*<<< orphan*/ * pg_map_arr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int CMDQ_INIT_CMDQ_LVL_MASK ; 
 int CMDQ_INIT_CMDQ_LVL_SFT ; 
 int CMDQ_INIT_CMDQ_SIZE_MASK ; 
 int CMDQ_INIT_CMDQ_SIZE_SFT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIRMWARE_FIRST_FLAG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PBL_LVL_0 ; 
 scalar_t__ RCFW_COMM_BASE_OFFSET ; 
 int RCFW_COMM_CONS_PCI_BAR_REGION ; 
 int RCFW_COMM_PCI_BAR_REGION ; 
 int RCFW_COMM_SIZE ; 
 int /*<<< orphan*/  RCFW_COMM_TRIG_OFFSET ; 
 int /*<<< orphan*/  RCFW_PF_COMM_PROD_OFFSET ; 
 int /*<<< orphan*/  RCFW_VF_COMM_PROD_OFFSET ; 
 int /*<<< orphan*/  __iowrite32_copy (int /*<<< orphan*/ *,struct cmdq_init*,int) ; 
 int /*<<< orphan*/  bnxt_qplib_disable_rcfw_channel (struct bnxt_qplib_rcfw*) ; 
 int bnxt_qplib_rcfw_start_irq (struct bnxt_qplib_rcfw*,int,int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* ioremap_nocache (scalar_t__,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnxt_qplib_enable_rcfw_channel(struct pci_dev *pdev,
				   struct bnxt_qplib_rcfw *rcfw,
				   int msix_vector,
				   int cp_bar_reg_off, int virt_fn,
				   int (*aeq_handler)(struct bnxt_qplib_rcfw *,
						      void *, void *))
{
	resource_size_t res_base;
	struct cmdq_init init;
	u16 bmap_size;
	int rc;

	/* General */
	rcfw->seq_num = 0;
	set_bit(FIRMWARE_FIRST_FLAG, &rcfw->flags);
	bmap_size = BITS_TO_LONGS(rcfw->cmdq_depth) * sizeof(unsigned long);
	rcfw->cmdq_bitmap = kzalloc(bmap_size, GFP_KERNEL);
	if (!rcfw->cmdq_bitmap)
		return -ENOMEM;
	rcfw->bmap_size = bmap_size;

	/* CMDQ */
	rcfw->cmdq_bar_reg = RCFW_COMM_PCI_BAR_REGION;
	res_base = pci_resource_start(pdev, rcfw->cmdq_bar_reg);
	if (!res_base)
		return -ENOMEM;

	rcfw->cmdq_bar_reg_iomem = ioremap_nocache(res_base +
					      RCFW_COMM_BASE_OFFSET,
					      RCFW_COMM_SIZE);
	if (!rcfw->cmdq_bar_reg_iomem) {
		dev_err(&rcfw->pdev->dev, "CMDQ BAR region %d mapping failed\n",
			rcfw->cmdq_bar_reg);
		return -ENOMEM;
	}

	rcfw->cmdq_bar_reg_prod_off = virt_fn ? RCFW_VF_COMM_PROD_OFFSET :
					RCFW_PF_COMM_PROD_OFFSET;

	rcfw->cmdq_bar_reg_trig_off = RCFW_COMM_TRIG_OFFSET;

	/* CREQ */
	rcfw->creq_bar_reg = RCFW_COMM_CONS_PCI_BAR_REGION;
	res_base = pci_resource_start(pdev, rcfw->creq_bar_reg);
	if (!res_base)
		dev_err(&rcfw->pdev->dev,
			"CREQ BAR region %d resc start is 0!\n",
			rcfw->creq_bar_reg);
	/* Unconditionally map 8 bytes to support 57500 series */
	rcfw->creq_bar_reg_iomem = ioremap_nocache(res_base + cp_bar_reg_off,
						   8);
	if (!rcfw->creq_bar_reg_iomem) {
		dev_err(&rcfw->pdev->dev, "CREQ BAR region %d mapping failed\n",
			rcfw->creq_bar_reg);
		iounmap(rcfw->cmdq_bar_reg_iomem);
		rcfw->cmdq_bar_reg_iomem = NULL;
		return -ENOMEM;
	}
	rcfw->creq_qp_event_processed = 0;
	rcfw->creq_func_event_processed = 0;

	if (aeq_handler)
		rcfw->aeq_handler = aeq_handler;
	init_waitqueue_head(&rcfw->waitq);

	rc = bnxt_qplib_rcfw_start_irq(rcfw, msix_vector, true);
	if (rc) {
		dev_err(&rcfw->pdev->dev,
			"Failed to request IRQ for CREQ rc = 0x%x\n", rc);
		bnxt_qplib_disable_rcfw_channel(rcfw);
		return rc;
	}

	init.cmdq_pbl = cpu_to_le64(rcfw->cmdq.pbl[PBL_LVL_0].pg_map_arr[0]);
	init.cmdq_size_cmdq_lvl = cpu_to_le16(
		((rcfw->cmdq_depth << CMDQ_INIT_CMDQ_SIZE_SFT) &
		 CMDQ_INIT_CMDQ_SIZE_MASK) |
		((rcfw->cmdq.level << CMDQ_INIT_CMDQ_LVL_SFT) &
		 CMDQ_INIT_CMDQ_LVL_MASK));
	init.creq_ring_id = cpu_to_le16(rcfw->creq_ring_id);

	/* Write to the Bono mailbox register */
	__iowrite32_copy(rcfw->cmdq_bar_reg_iomem, &init, sizeof(init) / 4);
	return 0;
}