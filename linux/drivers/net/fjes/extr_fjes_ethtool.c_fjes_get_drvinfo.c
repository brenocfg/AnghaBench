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
struct platform_device {char* name; } ;
struct net_device {int dummy; } ;
struct fjes_adapter {struct platform_device* plat_dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* fjes_driver_name ; 
 char* fjes_driver_version ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void fjes_get_drvinfo(struct net_device *netdev,
			     struct ethtool_drvinfo *drvinfo)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);
	struct platform_device *plat_dev;

	plat_dev = adapter->plat_dev;

	strlcpy(drvinfo->driver, fjes_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, fjes_driver_version,
		sizeof(drvinfo->version));

	strlcpy(drvinfo->fw_version, "none", sizeof(drvinfo->fw_version));
	snprintf(drvinfo->bus_info, sizeof(drvinfo->bus_info),
		 "platform:%s", plat_dev->name);
}