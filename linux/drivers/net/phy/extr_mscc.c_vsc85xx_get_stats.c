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
struct vsc8531_private {int nstats; } ;
struct phy_device {struct vsc8531_private* priv; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsc85xx_get_stat (struct phy_device*,int) ; 

__attribute__((used)) static void vsc85xx_get_stats(struct phy_device *phydev,
			      struct ethtool_stats *stats, u64 *data)
{
	struct vsc8531_private *priv = phydev->priv;
	int i;

	if (!priv)
		return;

	for (i = 0; i < priv->nstats; i++)
		data[i] = vsc85xx_get_stat(phydev, i);
}