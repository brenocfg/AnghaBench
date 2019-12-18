#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mvumi_hba {int request_id_enabled; TYPE_1__* pdev; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  regs; int /*<<< orphan*/  handshake_page_phys; int /*<<< orphan*/  handshake_page; int /*<<< orphan*/ * instancet; void* max_sge; int /*<<< orphan*/  io_seq; } ;
struct TYPE_5__ {int device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HSP_MAX_SIZE ; 
 void* MVUMI_MAX_SG_ENTRY ; 
 int /*<<< orphan*/  MV_DRIVER_NAME ; 
#define  PCI_DEVICE_ID_MARVELL_MV9143 129 
#define  PCI_DEVICE_ID_MARVELL_MV9580 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int mvumi_alloc_cmds (struct mvumi_hba*) ; 
 int mvumi_cfg_hw_reg (struct mvumi_hba*) ; 
 int /*<<< orphan*/  mvumi_instance_9143 ; 
 int /*<<< orphan*/  mvumi_instance_9580 ; 
 int mvumi_map_pci_addr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvumi_release_mem_resource (struct mvumi_hba*) ; 
 scalar_t__ mvumi_start (struct mvumi_hba*) ; 
 int /*<<< orphan*/  mvumi_unmap_pci_addr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_1__*) ; 
 scalar_t__ pci_request_regions (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvumi_init_fw(struct mvumi_hba *mhba)
{
	int ret = 0;

	if (pci_request_regions(mhba->pdev, MV_DRIVER_NAME)) {
		dev_err(&mhba->pdev->dev, "IO memory region busy!\n");
		return -EBUSY;
	}
	ret = mvumi_map_pci_addr(mhba->pdev, mhba->base_addr);
	if (ret)
		goto fail_ioremap;

	switch (mhba->pdev->device) {
	case PCI_DEVICE_ID_MARVELL_MV9143:
		mhba->instancet = &mvumi_instance_9143;
		mhba->io_seq = 0;
		mhba->max_sge = MVUMI_MAX_SG_ENTRY;
		mhba->request_id_enabled = 1;
		break;
	case PCI_DEVICE_ID_MARVELL_MV9580:
		mhba->instancet = &mvumi_instance_9580;
		mhba->io_seq = 0;
		mhba->max_sge = MVUMI_MAX_SG_ENTRY;
		break;
	default:
		dev_err(&mhba->pdev->dev, "device 0x%x not supported!\n",
							mhba->pdev->device);
		mhba->instancet = NULL;
		ret = -EINVAL;
		goto fail_alloc_mem;
	}
	dev_dbg(&mhba->pdev->dev, "device id : %04X is found.\n",
							mhba->pdev->device);
	ret = mvumi_cfg_hw_reg(mhba);
	if (ret) {
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for reg\n");
		ret = -ENOMEM;
		goto fail_alloc_mem;
	}
	mhba->handshake_page = dma_alloc_coherent(&mhba->pdev->dev,
			HSP_MAX_SIZE, &mhba->handshake_page_phys, GFP_KERNEL);
	if (!mhba->handshake_page) {
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for handshake\n");
		ret = -ENOMEM;
		goto fail_alloc_page;
	}

	if (mvumi_start(mhba)) {
		ret = -EINVAL;
		goto fail_ready_state;
	}
	ret = mvumi_alloc_cmds(mhba);
	if (ret)
		goto fail_ready_state;

	return 0;

fail_ready_state:
	mvumi_release_mem_resource(mhba);
	dma_free_coherent(&mhba->pdev->dev, HSP_MAX_SIZE,
		mhba->handshake_page, mhba->handshake_page_phys);
fail_alloc_page:
	kfree(mhba->regs);
fail_alloc_mem:
	mvumi_unmap_pci_addr(mhba->pdev, mhba->base_addr);
fail_ioremap:
	pci_release_regions(mhba->pdev);

	return ret;
}