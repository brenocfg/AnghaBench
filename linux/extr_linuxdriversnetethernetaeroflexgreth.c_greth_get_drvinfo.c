#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct greth_private {TYPE_2__* dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 char* dev_driver_string (TYPE_2__*) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void greth_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct greth_private *greth = netdev_priv(dev);

	strlcpy(info->driver, dev_driver_string(greth->dev),
		sizeof(info->driver));
	strlcpy(info->version, "revision: 1.0", sizeof(info->version));
	strlcpy(info->bus_info, greth->dev->bus->name, sizeof(info->bus_info));
	strlcpy(info->fw_version, "N/A", sizeof(info->fw_version));
}