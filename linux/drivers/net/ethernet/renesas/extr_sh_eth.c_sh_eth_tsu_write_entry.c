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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sh_eth_private {scalar_t__ tsu_addr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ sh_eth_tsu_busy (struct net_device*) ; 

__attribute__((used)) static int sh_eth_tsu_write_entry(struct net_device *ndev, u16 offset,
				  const u8 *addr)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u32 val;

	val = addr[0] << 24 | addr[1] << 16 | addr[2] << 8 | addr[3];
	iowrite32(val, mdp->tsu_addr + offset);
	if (sh_eth_tsu_busy(ndev) < 0)
		return -EBUSY;

	val = addr[4] << 8 | addr[5];
	iowrite32(val, mdp->tsu_addr + offset + 4);
	if (sh_eth_tsu_busy(ndev) < 0)
		return -EBUSY;

	return 0;
}