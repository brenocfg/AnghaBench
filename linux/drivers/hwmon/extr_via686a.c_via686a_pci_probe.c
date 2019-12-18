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
typedef  int u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  VIA686A_BASE_REG ; 
 int /*<<< orphan*/  VIA686A_ENABLE_REG ; 
 int VIA686A_EXTENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int force_addr ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 scalar_t__ pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_bridge ; 
 scalar_t__ via686a_device_add (int) ; 
 int /*<<< orphan*/  via686a_driver ; 

__attribute__((used)) static int via686a_pci_probe(struct pci_dev *dev,
				       const struct pci_device_id *id)
{
	u16 address, val;

	if (force_addr) {
		address = force_addr & ~(VIA686A_EXTENT - 1);
		dev_warn(&dev->dev, "Forcing ISA address 0x%x\n", address);
		if (PCIBIOS_SUCCESSFUL !=
		    pci_write_config_word(dev, VIA686A_BASE_REG, address | 1))
			return -ENODEV;
	}
	if (PCIBIOS_SUCCESSFUL !=
	    pci_read_config_word(dev, VIA686A_BASE_REG, &val))
		return -ENODEV;

	address = val & ~(VIA686A_EXTENT - 1);
	if (address == 0) {
		dev_err(&dev->dev,
			"base address not set - upgrade BIOS or use force_addr=0xaddr\n");
		return -ENODEV;
	}

	if (PCIBIOS_SUCCESSFUL !=
	    pci_read_config_word(dev, VIA686A_ENABLE_REG, &val))
		return -ENODEV;
	if (!(val & 0x0001)) {
		if (!force_addr) {
			dev_warn(&dev->dev,
				 "Sensors disabled, enable with force_addr=0x%x\n",
				 address);
			return -ENODEV;
		}

		dev_warn(&dev->dev, "Enabling sensors\n");
		if (PCIBIOS_SUCCESSFUL !=
		    pci_write_config_word(dev, VIA686A_ENABLE_REG,
					  val | 0x0001))
			return -ENODEV;
	}

	if (platform_driver_register(&via686a_driver))
		goto exit;

	/* Sets global pdev as a side effect */
	if (via686a_device_add(address))
		goto exit_unregister;

	/*
	 * Always return failure here.  This is to allow other drivers to bind
	 * to this pci device.  We don't really want to have control over the
	 * pci device, we only wanted to read as few register values from it.
	 */
	s_bridge = pci_dev_get(dev);
	return -ENODEV;

exit_unregister:
	platform_driver_unregister(&via686a_driver);
exit:
	return -ENODEV;
}