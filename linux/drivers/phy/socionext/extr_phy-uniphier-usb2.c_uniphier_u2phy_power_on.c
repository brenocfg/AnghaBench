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
struct uniphier_u2phy_priv {scalar_t__ vbus; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 struct uniphier_u2phy_priv* phy_get_drvdata (struct phy*) ; 
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int uniphier_u2phy_power_on(struct phy *phy)
{
	struct uniphier_u2phy_priv *priv = phy_get_drvdata(phy);
	int ret = 0;

	if (priv->vbus)
		ret = regulator_enable(priv->vbus);

	return ret;
}