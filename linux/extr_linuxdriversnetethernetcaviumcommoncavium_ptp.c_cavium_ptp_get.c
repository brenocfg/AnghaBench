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
struct pci_dev {int dummy; } ;
struct cavium_ptp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct cavium_ptp* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct cavium_ptp*) ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_CAVIUM_PTP ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_CAVIUM ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cavium_ptp* pci_get_drvdata (struct pci_dev*) ; 

struct cavium_ptp *cavium_ptp_get(void)
{
	struct cavium_ptp *ptp;
	struct pci_dev *pdev;

	pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
			      PCI_DEVICE_ID_CAVIUM_PTP, NULL);
	if (!pdev)
		return ERR_PTR(-ENODEV);

	ptp = pci_get_drvdata(pdev);
	if (!ptp)
		ptp = ERR_PTR(-EPROBE_DEFER);
	if (IS_ERR(ptp))
		pci_dev_put(pdev);

	return ptp;
}