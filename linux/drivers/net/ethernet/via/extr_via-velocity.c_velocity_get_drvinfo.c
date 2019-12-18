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
struct velocity_info {scalar_t__ pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* VELOCITY_NAME ; 
 char* VELOCITY_VERSION ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 char* pci_name (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void velocity_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct velocity_info *vptr = netdev_priv(dev);

	strlcpy(info->driver, VELOCITY_NAME, sizeof(info->driver));
	strlcpy(info->version, VELOCITY_VERSION, sizeof(info->version));
	if (vptr->pdev)
		strlcpy(info->bus_info, pci_name(vptr->pdev),
						sizeof(info->bus_info));
	else
		strlcpy(info->bus_info, "platform", sizeof(info->bus_info));
}