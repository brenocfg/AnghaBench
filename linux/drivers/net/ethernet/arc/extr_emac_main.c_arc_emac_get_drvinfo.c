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
struct ethtool_drvinfo {int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct arc_emac_priv {int /*<<< orphan*/  drv_version; int /*<<< orphan*/  drv_name; } ;

/* Variables and functions */
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arc_emac_get_drvinfo(struct net_device *ndev,
				 struct ethtool_drvinfo *info)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);

	strlcpy(info->driver, priv->drv_name, sizeof(info->driver));
	strlcpy(info->version, priv->drv_version, sizeof(info->version));
}