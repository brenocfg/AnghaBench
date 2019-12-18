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
struct pci_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct lan743x_adapter {struct pci_dev* pdev; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  netif_info (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int pci_request_selected_regions (struct pci_dev*,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int lan743x_pci_init(struct lan743x_adapter *adapter,
			    struct pci_dev *pdev)
{
	unsigned long bars = 0;
	int ret;

	adapter->pdev = pdev;
	ret = pci_enable_device_mem(pdev);
	if (ret)
		goto return_error;

	netif_info(adapter, probe, adapter->netdev,
		   "PCI: Vendor ID = 0x%04X, Device ID = 0x%04X\n",
		   pdev->vendor, pdev->device);
	bars = pci_select_bars(pdev, IORESOURCE_MEM);
	if (!test_bit(0, &bars))
		goto disable_device;

	ret = pci_request_selected_regions(pdev, bars, DRIVER_NAME);
	if (ret)
		goto disable_device;

	pci_set_master(pdev);
	return 0;

disable_device:
	pci_disable_device(adapter->pdev);

return_error:
	return ret;
}