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
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ pci_power_t ;

/* Variables and functions */
 int PCIBIOS_SET_FAILED ; 
 int PCI_PM_CTRL_STATE_MASK ; 
 int PM_OK_BITS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int pci_read_config_word (struct pci_dev*,int,int*) ; 
 int pci_set_power_state (struct pci_dev*,scalar_t__) ; 
 int pci_write_config_word (struct pci_dev*,int,int) ; 

__attribute__((used)) static int pm_ctrl_write(struct pci_dev *dev, int offset, u16 new_value,
			 void *data)
{
	int err;
	u16 old_value;
	pci_power_t new_state;

	err = pci_read_config_word(dev, offset, &old_value);
	if (err)
		goto out;

	new_state = (pci_power_t)(new_value & PCI_PM_CTRL_STATE_MASK);

	new_value &= PM_OK_BITS;
	if ((old_value & PM_OK_BITS) != new_value) {
		new_value = (old_value & ~PM_OK_BITS) | new_value;
		err = pci_write_config_word(dev, offset, new_value);
		if (err)
			goto out;
	}

	/* Let pci core handle the power management change */
	dev_dbg(&dev->dev, "set power state to %x\n", new_state);
	err = pci_set_power_state(dev, new_state);
	if (err) {
		err = PCIBIOS_SET_FAILED;
		goto out;
	}

 out:
	return err;
}