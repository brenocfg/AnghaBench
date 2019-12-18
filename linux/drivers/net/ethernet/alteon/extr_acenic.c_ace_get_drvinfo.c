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
struct ace_private {int firmware_major; int firmware_minor; int firmware_fix; scalar_t__ pdev; } ;

/* Variables and functions */
 struct ace_private* netdev_priv (struct net_device*) ; 
 char* pci_name (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ace_get_drvinfo(struct net_device *dev,
			    struct ethtool_drvinfo *info)
{
	struct ace_private *ap = netdev_priv(dev);

	strlcpy(info->driver, "acenic", sizeof(info->driver));
	snprintf(info->version, sizeof(info->version), "%i.%i.%i",
		 ap->firmware_major, ap->firmware_minor,
		 ap->firmware_fix);

	if (ap->pdev)
		strlcpy(info->bus_info, pci_name(ap->pdev),
			sizeof(info->bus_info));

}