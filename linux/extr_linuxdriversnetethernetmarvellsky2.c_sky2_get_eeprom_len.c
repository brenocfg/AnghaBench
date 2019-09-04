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
struct sky2_port {struct sky2_hw* hw; } ;
struct sky2_hw {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEV_REG2 ; 
 int PCI_VPD_ROM_SZ ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int sky2_pci_read16 (struct sky2_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_get_eeprom_len(struct net_device *dev)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;
	u16 reg2;

	reg2 = sky2_pci_read16(hw, PCI_DEV_REG2);
	return 1 << ( ((reg2 & PCI_VPD_ROM_SZ) >> 14) + 8);
}