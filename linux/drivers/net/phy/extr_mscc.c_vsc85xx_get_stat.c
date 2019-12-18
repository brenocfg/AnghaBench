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
typedef  int u64 ;
struct vsc8531_private {int* stats; TYPE_1__* hw_stats; } ;
struct phy_device {struct vsc8531_private* priv; } ;
struct TYPE_2__ {int mask; int /*<<< orphan*/  reg; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int U64_MAX ; 
 int phy_read_paged (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 vsc85xx_get_stat(struct phy_device *phydev, int i)
{
	struct vsc8531_private *priv = phydev->priv;
	int val;

	val = phy_read_paged(phydev, priv->hw_stats[i].page,
			     priv->hw_stats[i].reg);
	if (val < 0)
		return U64_MAX;

	val = val & priv->hw_stats[i].mask;
	priv->stats[i] += val;

	return priv->stats[i];
}