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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct altera_tse_private {TYPE_1__* mac_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  megacore_revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_FWVERS_LEN ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void tse_get_drvinfo(struct net_device *dev,
			    struct ethtool_drvinfo *info)
{
	struct altera_tse_private *priv = netdev_priv(dev);
	u32 rev = ioread32(&priv->mac_dev->megacore_revision);

	strcpy(info->driver, "altera_tse");
	strcpy(info->version, "v8.0");
	snprintf(info->fw_version, ETHTOOL_FWVERS_LEN, "v%d.%d",
		 rev & 0xFFFF, (rev & 0xFFFF0000) >> 16);
	sprintf(info->bus_info, "platform");
}