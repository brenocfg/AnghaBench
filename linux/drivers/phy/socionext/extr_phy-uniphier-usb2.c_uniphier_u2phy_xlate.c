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
struct uniphier_u2phy_priv {struct phy* phy; struct uniphier_u2phy_priv* next; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct phy {TYPE_1__ dev; } ;
struct of_phandle_args {scalar_t__ np; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct uniphier_u2phy_priv* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *uniphier_u2phy_xlate(struct device *dev,
					struct of_phandle_args *args)
{
	struct uniphier_u2phy_priv *priv = dev_get_drvdata(dev);

	while (priv && args->np != priv->phy->dev.of_node)
		priv = priv->next;

	if (!priv) {
		dev_err(dev, "Failed to find appropriate phy\n");
		return ERR_PTR(-EINVAL);
	}

	return priv->phy;
}