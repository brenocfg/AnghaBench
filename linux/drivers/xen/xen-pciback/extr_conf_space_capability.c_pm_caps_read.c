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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int PCI_PM_CAP_PME_MASK ; 
 int pci_read_config_word (struct pci_dev*,int,int*) ; 

__attribute__((used)) static int pm_caps_read(struct pci_dev *dev, int offset, u16 *value,
			void *data)
{
	int err;
	u16 real_value;

	err = pci_read_config_word(dev, offset, &real_value);
	if (err)
		goto out;

	*value = real_value & ~PCI_PM_CAP_PME_MASK;

out:
	return err;
}