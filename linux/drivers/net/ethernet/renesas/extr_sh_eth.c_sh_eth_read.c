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
typedef  unsigned int u32 ;
typedef  scalar_t__ u16 ;
struct sh_eth_private {scalar_t__* reg_offset; scalar_t__ addr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SH_ETH_OFFSET_INVALID ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int ioread32 (scalar_t__) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 sh_eth_read(struct net_device *ndev, int enum_index)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u16 offset = mdp->reg_offset[enum_index];

	if (WARN_ON(offset == SH_ETH_OFFSET_INVALID))
		return ~0U;

	return ioread32(mdp->addr + offset);
}