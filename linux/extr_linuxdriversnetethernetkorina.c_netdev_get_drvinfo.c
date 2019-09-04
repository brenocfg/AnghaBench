#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct korina_private {TYPE_1__* dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 struct korina_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void netdev_get_drvinfo(struct net_device *dev,
				struct ethtool_drvinfo *info)
{
	struct korina_private *lp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, sizeof(info->driver));
	strlcpy(info->version, DRV_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, lp->dev->name, sizeof(info->bus_info));
}