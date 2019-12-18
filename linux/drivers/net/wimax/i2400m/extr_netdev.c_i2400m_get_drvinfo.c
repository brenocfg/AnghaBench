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
struct TYPE_2__ {scalar_t__ parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct i2400m {scalar_t__ fw_name; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* KBUILD_MODNAME ; 
 char* dev_name (scalar_t__) ; 
 struct i2400m* net_dev_to_i2400m (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void i2400m_get_drvinfo(struct net_device *net_dev,
			       struct ethtool_drvinfo *info)
{
	struct i2400m *i2400m = net_dev_to_i2400m(net_dev);

	strlcpy(info->driver, KBUILD_MODNAME, sizeof(info->driver));
	strlcpy(info->fw_version, i2400m->fw_name ? : "",
		sizeof(info->fw_version));
	if (net_dev->dev.parent)
		strlcpy(info->bus_info, dev_name(net_dev->dev.parent),
			sizeof(info->bus_info));
}