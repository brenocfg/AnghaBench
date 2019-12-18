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
struct uniphier_u2phy_priv {TYPE_3__* data; int /*<<< orphan*/  regmap; } ;
struct phy {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {TYPE_1__ config1; TYPE_2__ config0; } ;

/* Variables and functions */
 struct uniphier_u2phy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_u2phy_init(struct phy *phy)
{
	struct uniphier_u2phy_priv *priv = phy_get_drvdata(phy);

	if (!priv->data)
		return 0;

	regmap_write(priv->regmap, priv->data->config0.offset,
		     priv->data->config0.value);
	regmap_write(priv->regmap, priv->data->config1.offset,
		     priv->data->config1.value);

	return 0;
}