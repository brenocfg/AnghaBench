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
struct k3_priv {scalar_t__ ctrl_id; int /*<<< orphan*/ * reg; } ;
struct dw_mci {struct k3_priv* priv; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ TIMING_MODE ; 
 struct k3_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dw_mci_hi6220_parse_dt(struct dw_mci *host)
{
	struct k3_priv *priv;

	priv = devm_kzalloc(host->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->reg = syscon_regmap_lookup_by_phandle(host->dev->of_node,
					 "hisilicon,peripheral-syscon");
	if (IS_ERR(priv->reg))
		priv->reg = NULL;

	priv->ctrl_id = of_alias_get_id(host->dev->of_node, "mshc");
	if (priv->ctrl_id < 0)
		priv->ctrl_id = 0;

	if (priv->ctrl_id >= TIMING_MODE)
		return -EINVAL;

	host->priv = priv;
	return 0;
}