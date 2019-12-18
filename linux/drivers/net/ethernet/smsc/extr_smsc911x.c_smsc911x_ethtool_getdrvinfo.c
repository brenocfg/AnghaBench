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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMSC_CHIPNAME ; 
 int /*<<< orphan*/  SMSC_DRV_VERSION ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smsc911x_ethtool_getdrvinfo(struct net_device *dev,
					struct ethtool_drvinfo *info)
{
	strlcpy(info->driver, SMSC_CHIPNAME, sizeof(info->driver));
	strlcpy(info->version, SMSC_DRV_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, dev_name(dev->dev.parent),
		sizeof(info->bus_info));
}