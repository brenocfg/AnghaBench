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
 int ioread32 (scalar_t__) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void sh_eth_tsu_read_entry(struct net_device *ndev, u16 offset, u8 *addr)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u32 val;

	val = ioread32(mdp->tsu_addr + offset);
	addr[0] = (val >> 24) & 0xff;
	addr[1] = (val >> 16) & 0xff;
	addr[2] = (val >> 8) & 0xff;
	addr[3] = val & 0xff;
	val = ioread32(mdp->tsu_addr + offset + 4);
	addr[4] = (val >> 8) & 0xff;
	addr[5] = val & 0xff;
}