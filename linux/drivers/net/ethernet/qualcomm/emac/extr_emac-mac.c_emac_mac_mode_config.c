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
typedef  int u32 ;
struct net_device {int features; int flags; } ;
struct emac_adapter {scalar_t__ base; struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ EMAC_MAC_CTRL ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MAC_LP_EN ; 
 int MULTI_ALL ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int PROM_MODE ; 
 int VLAN_STRIP ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void emac_mac_mode_config(struct emac_adapter *adpt)
{
	struct net_device *netdev = adpt->netdev;
	u32 mac;

	mac = readl(adpt->base + EMAC_MAC_CTRL);
	mac &= ~(VLAN_STRIP | PROM_MODE | MULTI_ALL | MAC_LP_EN);

	if (netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		mac |= VLAN_STRIP;

	if (netdev->flags & IFF_PROMISC)
		mac |= PROM_MODE;

	if (netdev->flags & IFF_ALLMULTI)
		mac |= MULTI_ALL;

	writel(mac, adpt->base + EMAC_MAC_CTRL);
}