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
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct emac_instance {int cell_index; TYPE_2__* ofdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 char* DRV_VERSION ; 
 struct emac_instance* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void emac_ethtool_get_drvinfo(struct net_device *ndev,
				     struct ethtool_drvinfo *info)
{
	struct emac_instance *dev = netdev_priv(ndev);

	strlcpy(info->driver, "ibm_emac", sizeof(info->driver));
	strlcpy(info->version, DRV_VERSION, sizeof(info->version));
	snprintf(info->bus_info, sizeof(info->bus_info), "PPC 4xx EMAC-%d %pOF",
		 dev->cell_index, dev->ofdev->dev.of_node);
}