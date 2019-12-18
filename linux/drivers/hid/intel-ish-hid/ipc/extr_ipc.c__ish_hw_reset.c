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
typedef  int /*<<< orphan*/  uint16_t ;
struct pci_dev {scalar_t__ pm_cap; int /*<<< orphan*/  d3_delay; int /*<<< orphan*/  dev; } ;
struct ishtp_device {int /*<<< orphan*/  dev_state; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ISHTP_DEV_RESETTING ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ PCI_PM_CTRL ; 
 int /*<<< orphan*/  PCI_PM_CTRL_STATE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ish_disable_dma (struct ishtp_device*) ; 
 int /*<<< orphan*/  ish_wakeup (struct ishtp_device*) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int pci_reset_function (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ish_hw_reset(struct ishtp_device *dev)
{
	struct pci_dev *pdev = dev->pdev;
	int	rv;
	uint16_t csr;

	if (!pdev)
		return	-ENODEV;

	rv = pci_reset_function(pdev);
	if (!rv)
		dev->dev_state = ISHTP_DEV_RESETTING;

	if (!pdev->pm_cap) {
		dev_err(&pdev->dev, "Can't reset - no PM caps\n");
		return	-EINVAL;
	}

	/* Disable dma communication between FW and host */
	if (ish_disable_dma(dev)) {
		dev_err(&pdev->dev,
			"Can't reset - stuck with DMA in-progress\n");
		return	-EBUSY;
	}

	pci_read_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, &csr);

	csr &= ~PCI_PM_CTRL_STATE_MASK;
	csr |= PCI_D3hot;
	pci_write_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, csr);

	mdelay(pdev->d3_delay);

	csr &= ~PCI_PM_CTRL_STATE_MASK;
	csr |= PCI_D0;
	pci_write_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, csr);

	/* Now we can enable ISH DMA operation and wakeup ISHFW */
	ish_wakeup(dev);

	return	0;
}