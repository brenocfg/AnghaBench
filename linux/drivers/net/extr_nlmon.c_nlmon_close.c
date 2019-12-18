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
struct nlmon {int /*<<< orphan*/  nt; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct nlmon* netdev_priv (struct net_device*) ; 
 int netlink_remove_tap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nlmon_close(struct net_device *dev)
{
	struct nlmon *nlmon = netdev_priv(dev);

	return netlink_remove_tap(&nlmon->nt);
}