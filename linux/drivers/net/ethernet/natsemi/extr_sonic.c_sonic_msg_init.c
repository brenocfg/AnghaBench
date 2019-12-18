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
struct sonic_local {int /*<<< orphan*/  msg_enable; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct sonic_local*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sonic_debug ; 
 int /*<<< orphan*/  version ; 
 int /*<<< orphan*/  version_printed ; 

__attribute__((used)) static void sonic_msg_init(struct net_device *dev)
{
	struct sonic_local *lp = netdev_priv(dev);

	lp->msg_enable = netif_msg_init(sonic_debug, 0);

	if (version_printed++ == 0)
		netif_dbg(lp, drv, dev, "%s", version);
}