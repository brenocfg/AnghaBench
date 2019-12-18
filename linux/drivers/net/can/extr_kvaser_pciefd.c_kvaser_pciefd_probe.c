#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct kvaser_pciefd {scalar_t__ reg_base; struct pci_dev* pci; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KVASER_PCIEFD_DRV_NAME ; 
 scalar_t__ KVASER_PCIEFD_IEN_REG ; 
 int KVASER_PCIEFD_IRQ_ALL_MSK ; 
 scalar_t__ KVASER_PCIEFD_IRQ_REG ; 
 int KVASER_PCIEFD_SRB_CMD_RDB0 ; 
 int KVASER_PCIEFD_SRB_CMD_RDB1 ; 
 scalar_t__ KVASER_PCIEFD_SRB_CMD_REG ; 
 scalar_t__ KVASER_PCIEFD_SRB_CTRL_REG ; 
 scalar_t__ KVASER_PCIEFD_SRB_IEN_REG ; 
 int KVASER_PCIEFD_SRB_IRQ_DOF0 ; 
 int KVASER_PCIEFD_SRB_IRQ_DOF1 ; 
 int KVASER_PCIEFD_SRB_IRQ_DPD0 ; 
 int KVASER_PCIEFD_SRB_IRQ_DPD1 ; 
 int KVASER_PCIEFD_SRB_IRQ_DUF0 ; 
 int KVASER_PCIEFD_SRB_IRQ_DUF1 ; 
 scalar_t__ KVASER_PCIEFD_SRB_IRQ_REG ; 
 struct kvaser_pciefd* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct kvaser_pciefd*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_irq_handler ; 
 int kvaser_pciefd_reg_candev (struct kvaser_pciefd*) ; 
 int kvaser_pciefd_setup_board (struct kvaser_pciefd*) ; 
 int kvaser_pciefd_setup_can_ctrls (struct kvaser_pciefd*) ; 
 int kvaser_pciefd_setup_dma (struct kvaser_pciefd*) ; 
 int /*<<< orphan*/  kvaser_pciefd_teardown_can_ctrls (struct kvaser_pciefd*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 scalar_t__ pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct kvaser_pciefd*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvaser_pciefd*) ; 

__attribute__((used)) static int kvaser_pciefd_probe(struct pci_dev *pdev,
			       const struct pci_device_id *id)
{
	int err;
	struct kvaser_pciefd *pcie;

	pcie = devm_kzalloc(&pdev->dev, sizeof(*pcie), GFP_KERNEL);
	if (!pcie)
		return -ENOMEM;

	pci_set_drvdata(pdev, pcie);
	pcie->pci = pdev;

	err = pci_enable_device(pdev);
	if (err)
		return err;

	err = pci_request_regions(pdev, KVASER_PCIEFD_DRV_NAME);
	if (err)
		goto err_disable_pci;

	pcie->reg_base = pci_iomap(pdev, 0, 0);
	if (!pcie->reg_base) {
		err = -ENOMEM;
		goto err_release_regions;
	}

	err = kvaser_pciefd_setup_board(pcie);
	if (err)
		goto err_pci_iounmap;

	err = kvaser_pciefd_setup_dma(pcie);
	if (err)
		goto err_pci_iounmap;

	pci_set_master(pdev);

	err = kvaser_pciefd_setup_can_ctrls(pcie);
	if (err)
		goto err_teardown_can_ctrls;

	iowrite32(KVASER_PCIEFD_SRB_IRQ_DPD0 | KVASER_PCIEFD_SRB_IRQ_DPD1,
		  pcie->reg_base + KVASER_PCIEFD_SRB_IRQ_REG);

	iowrite32(KVASER_PCIEFD_SRB_IRQ_DPD0 | KVASER_PCIEFD_SRB_IRQ_DPD1 |
		  KVASER_PCIEFD_SRB_IRQ_DOF0 | KVASER_PCIEFD_SRB_IRQ_DOF1 |
		  KVASER_PCIEFD_SRB_IRQ_DUF0 | KVASER_PCIEFD_SRB_IRQ_DUF1,
		  pcie->reg_base + KVASER_PCIEFD_SRB_IEN_REG);

	/* Reset IRQ handling, expected to be off before */
	iowrite32(KVASER_PCIEFD_IRQ_ALL_MSK,
		  pcie->reg_base + KVASER_PCIEFD_IRQ_REG);
	iowrite32(KVASER_PCIEFD_IRQ_ALL_MSK,
		  pcie->reg_base + KVASER_PCIEFD_IEN_REG);

	/* Ready the DMA buffers */
	iowrite32(KVASER_PCIEFD_SRB_CMD_RDB0,
		  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);
	iowrite32(KVASER_PCIEFD_SRB_CMD_RDB1,
		  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);

	err = request_irq(pcie->pci->irq, kvaser_pciefd_irq_handler,
			  IRQF_SHARED, KVASER_PCIEFD_DRV_NAME, pcie);
	if (err)
		goto err_teardown_can_ctrls;

	err = kvaser_pciefd_reg_candev(pcie);
	if (err)
		goto err_free_irq;

	return 0;

err_free_irq:
	free_irq(pcie->pci->irq, pcie);

err_teardown_can_ctrls:
	kvaser_pciefd_teardown_can_ctrls(pcie);
	iowrite32(0, pcie->reg_base + KVASER_PCIEFD_SRB_CTRL_REG);
	pci_clear_master(pdev);

err_pci_iounmap:
	pci_iounmap(pdev, pcie->reg_base);

err_release_regions:
	pci_release_regions(pdev);

err_disable_pci:
	pci_disable_device(pdev);

	return err;
}