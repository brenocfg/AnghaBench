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
typedef  int /*<<< orphan*/  u32 ;
struct netdata_local {int /*<<< orphan*/  msg_enable; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct netdata_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 lpc_eth_ethtool_getmsglevel(struct net_device *ndev)
{
	struct netdata_local *pldat = netdev_priv(ndev);

	return pldat->msg_enable;
}