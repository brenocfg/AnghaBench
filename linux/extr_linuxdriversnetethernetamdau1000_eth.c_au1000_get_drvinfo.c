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
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct au1000_private {int mac_id; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 char* DRV_VERSION ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
au1000_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct au1000_private *aup = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, sizeof(info->driver));
	strlcpy(info->version, DRV_VERSION, sizeof(info->version));
	snprintf(info->bus_info, sizeof(info->bus_info), "%s %d", DRV_NAME,
		 aup->mac_id);
}