#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev; } ;
struct fec_enet_private {TYPE_3__* pdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void fec_enet_get_drvinfo(struct net_device *ndev,
				 struct ethtool_drvinfo *info)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

	strlcpy(info->driver, fep->pdev->dev.driver->name,
		sizeof(info->driver));
	strlcpy(info->version, "Revision: 1.0", sizeof(info->version));
	strlcpy(info->bus_info, dev_name(&ndev->dev), sizeof(info->bus_info));
}