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
struct vsc8531_private {int nstats; } ;
struct phy_device {struct vsc8531_private* priv; } ;

/* Variables and functions */

__attribute__((used)) static int vsc85xx_get_sset_count(struct phy_device *phydev)
{
	struct vsc8531_private *priv = phydev->priv;

	if (!priv)
		return 0;

	return priv->nstats;
}