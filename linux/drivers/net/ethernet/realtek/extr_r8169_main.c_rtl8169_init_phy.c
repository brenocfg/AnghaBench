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
struct rtl8169_private {scalar_t__ mac_version; int /*<<< orphan*/  phydev; int /*<<< orphan*/  pci_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 scalar_t__ RTL_GIGA_MAC_VER_06 ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  genphy_soft_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct rtl8169_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_speed_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_hw_phy_config (struct net_device*) ; 

__attribute__((used)) static void rtl8169_init_phy(struct net_device *dev, struct rtl8169_private *tp)
{
	rtl_hw_phy_config(dev);

	if (tp->mac_version <= RTL_GIGA_MAC_VER_06) {
		pci_write_config_byte(tp->pci_dev, PCI_LATENCY_TIMER, 0x40);
		pci_write_config_byte(tp->pci_dev, PCI_CACHE_LINE_SIZE, 0x08);
		netif_dbg(tp, drv, dev,
			  "Set MAC Reg C+CR Offset 0x82h = 0x01h\n");
		RTL_W8(tp, 0x82, 0x01);
	}

	/* We may have called phy_speed_down before */
	phy_speed_up(tp->phydev);

	genphy_soft_reset(tp->phydev);
}