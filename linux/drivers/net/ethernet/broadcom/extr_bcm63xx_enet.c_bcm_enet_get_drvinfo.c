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
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* bcm_enet_driver_name ; 
 char* bcm_enet_driver_version ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void bcm_enet_get_drvinfo(struct net_device *netdev,
				 struct ethtool_drvinfo *drvinfo)
{
	strlcpy(drvinfo->driver, bcm_enet_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, bcm_enet_driver_version,
		sizeof(drvinfo->version));
	strlcpy(drvinfo->fw_version, "N/A", sizeof(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, "bcm63xx", sizeof(drvinfo->bus_info));
}