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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct arcnet_local {scalar_t__ backplane; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct net_device* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t backplane_mode_show(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	struct net_device *net_dev = to_net_dev(dev);
	struct arcnet_local *lp = netdev_priv(net_dev);

	return sprintf(buf, "%s\n", lp->backplane ? "true" : "false");
}