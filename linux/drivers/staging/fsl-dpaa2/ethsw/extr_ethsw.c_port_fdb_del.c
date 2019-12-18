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
typedef  int /*<<< orphan*/  u16 ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct ndmsg {int dummy; } ;

/* Variables and functions */
 int ethsw_port_fdb_del_mc (int /*<<< orphan*/ ,unsigned char const*) ; 
 int ethsw_port_fdb_del_uc (int /*<<< orphan*/ ,unsigned char const*) ; 
 scalar_t__ is_unicast_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static int port_fdb_del(struct ndmsg *ndm, struct nlattr *tb[],
			struct net_device *dev,
			const unsigned char *addr, u16 vid)
{
	if (is_unicast_ether_addr(addr))
		return ethsw_port_fdb_del_uc(netdev_priv(dev),
					     addr);
	else
		return ethsw_port_fdb_del_mc(netdev_priv(dev),
					     addr);
}