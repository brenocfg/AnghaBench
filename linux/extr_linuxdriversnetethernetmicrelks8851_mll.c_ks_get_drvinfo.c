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
 char* DRV_NAME ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ks_get_drvinfo(struct net_device *netdev,
			       struct ethtool_drvinfo *di)
{
	strlcpy(di->driver, DRV_NAME, sizeof(di->driver));
	strlcpy(di->version, "1.00", sizeof(di->version));
	strlcpy(di->bus_info, dev_name(netdev->dev.parent),
		sizeof(di->bus_info));
}