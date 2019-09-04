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
struct net_device {int /*<<< orphan*/  dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_DRIVER_NAME ; 
 int /*<<< orphan*/  MVPP2_DRIVER_VERSION ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvpp2_ethtool_get_drvinfo(struct net_device *dev,
				      struct ethtool_drvinfo *drvinfo)
{
	strlcpy(drvinfo->driver, MVPP2_DRIVER_NAME,
		sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, MVPP2_DRIVER_VERSION,
		sizeof(drvinfo->version));
	strlcpy(drvinfo->bus_info, dev_name(&dev->dev),
		sizeof(drvinfo->bus_info));
}