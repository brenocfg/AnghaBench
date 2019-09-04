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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ishtp_device {int /*<<< orphan*/  dev_state; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISHTP_DEV_DISABLED ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ish_clr_host_rdy (struct ishtp_device*) ; 
 scalar_t__ ish_disable_dma (struct ishtp_device*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

void	ish_device_disable(struct ishtp_device *dev)
{
	struct pci_dev *pdev = dev->pdev;

	if (!pdev)
		return;

	/* Disable dma communication between FW and host */
	if (ish_disable_dma(dev)) {
		dev_err(&pdev->dev,
			"Can't reset - stuck with DMA in-progress\n");
		return;
	}

	/* Put ISH to D3hot state for power saving */
	pci_set_power_state(pdev, PCI_D3hot);

	dev->dev_state = ISHTP_DEV_DISABLED;
	ish_clr_host_rdy(dev);
}