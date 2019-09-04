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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_4 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_5 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int p1_base (struct pci_dev*) ; 
 int p2_base (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int setup_cxl_bars(struct pci_dev *dev)
{
	/* Safety check in case we get backported to < 3.17 without M64 */
	if ((p1_base(dev) < 0x100000000ULL) ||
	    (p2_base(dev) < 0x100000000ULL)) {
		dev_err(&dev->dev, "ABORTING: M32 BAR assignment incompatible with CXL\n");
		return -ENODEV;
	}

	/*
	 * BAR 4/5 has a special meaning for CXL and must be programmed with a
	 * special value corresponding to the CXL protocol address range.
	 * For POWER 8/9 that means bits 48:49 must be set to 10
	 */
	pci_write_config_dword(dev, PCI_BASE_ADDRESS_4, 0x00000000);
	pci_write_config_dword(dev, PCI_BASE_ADDRESS_5, 0x00020000);

	return 0;
}