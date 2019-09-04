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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  RT2880_PCI_REG_CONFIG_ADDR ; 
 int /*<<< orphan*/  RT2880_PCI_REG_CONFIG_DATA ; 
 int /*<<< orphan*/  rt2880_pci_get_cfgaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rt2880_pci_lock ; 
 int /*<<< orphan*/  rt2880_pci_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2880_pci_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline u32 rt2880_pci_read_u32(unsigned long reg)
{
	unsigned long flags;
	u32 address;
	u32 ret;

	address = rt2880_pci_get_cfgaddr(0, 0, 0, reg);

	spin_lock_irqsave(&rt2880_pci_lock, flags);
	rt2880_pci_reg_write(address, RT2880_PCI_REG_CONFIG_ADDR);
	ret = rt2880_pci_reg_read(RT2880_PCI_REG_CONFIG_DATA);
	spin_unlock_irqrestore(&rt2880_pci_lock, flags);

	return ret;
}