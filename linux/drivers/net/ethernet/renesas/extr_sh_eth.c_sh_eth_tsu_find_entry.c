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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sh_eth_private {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ETH_ALEN ; 
 int SH_ETH_TSU_CAM_ENTRIES ; 
 int /*<<< orphan*/  TSU_ADRH0 ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int sh_eth_tsu_get_offset (struct sh_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_tsu_read_entry (struct net_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sh_eth_tsu_find_entry(struct net_device *ndev, const u8 *addr)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u16 reg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADRH0);
	int i;
	u8 c_addr[ETH_ALEN];

	for (i = 0; i < SH_ETH_TSU_CAM_ENTRIES; i++, reg_offset += 8) {
		sh_eth_tsu_read_entry(ndev, reg_offset, c_addr);
		if (ether_addr_equal(addr, c_addr))
			return i;
	}

	return -ENOENT;
}