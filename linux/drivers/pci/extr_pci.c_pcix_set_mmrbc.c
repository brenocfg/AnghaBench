#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {int bus_flags; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int EIO ; 
 int PCI_BUS_FLAGS_NO_MMRBC ; 
 int /*<<< orphan*/  PCI_CAP_ID_PCIX ; 
 scalar_t__ PCI_X_CMD ; 
 int PCI_X_CMD_MAX_READ ; 
 scalar_t__ PCI_X_STATUS ; 
 int PCI_X_STATUS_MAX_READ ; 
 int ffs (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 scalar_t__ pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 scalar_t__ pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 

int pcix_set_mmrbc(struct pci_dev *dev, int mmrbc)
{
	int cap;
	u32 stat, v, o;
	u16 cmd;

	if (mmrbc < 512 || mmrbc > 4096 || !is_power_of_2(mmrbc))
		return -EINVAL;

	v = ffs(mmrbc) - 10;

	cap = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	if (!cap)
		return -EINVAL;

	if (pci_read_config_dword(dev, cap + PCI_X_STATUS, &stat))
		return -EINVAL;

	if (v > (stat & PCI_X_STATUS_MAX_READ) >> 21)
		return -E2BIG;

	if (pci_read_config_word(dev, cap + PCI_X_CMD, &cmd))
		return -EINVAL;

	o = (cmd & PCI_X_CMD_MAX_READ) >> 2;
	if (o != v) {
		if (v > o && (dev->bus->bus_flags & PCI_BUS_FLAGS_NO_MMRBC))
			return -EIO;

		cmd &= ~PCI_X_CMD_MAX_READ;
		cmd |= v << 2;
		if (pci_write_config_word(dev, cap + PCI_X_CMD, cmd))
			return -EIO;
	}
	return 0;
}