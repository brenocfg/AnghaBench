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
struct skge_port {TYPE_1__* hw; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEV_REG2 ; 
 int PCI_VPD_ROM_SZ ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int skge_get_eeprom_len(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);
	u32 reg2;

	pci_read_config_dword(skge->hw->pdev, PCI_DEV_REG2, &reg2);
	return 1 << (((reg2 & PCI_VPD_ROM_SZ) >> 14) + 8);
}