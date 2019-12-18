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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sh_eth_private {TYPE_1__* cd; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsu; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int SH_ETH_TSU_CAM_ENTRIES ; 
 int /*<<< orphan*/  TSU_ADRH0 ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_tsu_del_entry (struct net_device*,int /*<<< orphan*/ *) ; 
 int sh_eth_tsu_get_offset (struct sh_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_tsu_read_entry (struct net_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_eth_tsu_purge_mcast(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u16 reg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADRH0);
	u8 addr[ETH_ALEN];
	int i;

	if (!mdp->cd->tsu)
		return;

	for (i = 0; i < SH_ETH_TSU_CAM_ENTRIES; i++, reg_offset += 8) {
		sh_eth_tsu_read_entry(ndev, reg_offset, addr);
		if (is_multicast_ether_addr(addr))
			sh_eth_tsu_del_entry(ndev, addr);
	}
}