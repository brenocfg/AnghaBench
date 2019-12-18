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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_name (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

int gether_get_ifname(struct net_device *net, char *name, int len)
{
	int ret;

	rtnl_lock();
	ret = scnprintf(name, len, "%s\n", netdev_name(net));
	rtnl_unlock();
	return ret;
}