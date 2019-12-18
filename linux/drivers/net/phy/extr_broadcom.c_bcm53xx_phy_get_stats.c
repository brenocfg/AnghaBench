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
typedef  int /*<<< orphan*/  u64 ;
struct phy_device {struct bcm53xx_phy_priv* priv; } ;
struct ethtool_stats {int dummy; } ;
struct bcm53xx_phy_priv {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_phy_get_stats (struct phy_device*,int /*<<< orphan*/ ,struct ethtool_stats*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm53xx_phy_get_stats(struct phy_device *phydev,
				  struct ethtool_stats *stats, u64 *data)
{
	struct bcm53xx_phy_priv *priv = phydev->priv;

	bcm_phy_get_stats(phydev, priv->stats, stats, data);
}