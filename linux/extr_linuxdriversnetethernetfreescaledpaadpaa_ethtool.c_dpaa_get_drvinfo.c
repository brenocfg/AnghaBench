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
struct TYPE_4__ {TYPE_1__* parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,int) ; 
 int snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dpaa_get_drvinfo(struct net_device *net_dev,
			     struct ethtool_drvinfo *drvinfo)
{
	int len;

	strlcpy(drvinfo->driver, KBUILD_MODNAME,
		sizeof(drvinfo->driver));
	len = snprintf(drvinfo->version, sizeof(drvinfo->version),
		       "%X", 0);
	len = snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		       "%X", 0);

	if (len >= sizeof(drvinfo->fw_version)) {
		/* Truncated output */
		netdev_notice(net_dev, "snprintf() = %d\n", len);
	}
	strlcpy(drvinfo->bus_info, dev_name(net_dev->dev.parent->parent),
		sizeof(drvinfo->bus_info));
}