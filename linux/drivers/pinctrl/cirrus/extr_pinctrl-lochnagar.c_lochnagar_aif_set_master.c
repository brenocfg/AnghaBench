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
struct regmap {int dummy; } ;
struct lochnagar_pin_priv {int /*<<< orphan*/  dev; struct lochnagar_group* groups; TYPE_1__* lochnagar; } ;
struct lochnagar_group {scalar_t__ type; int /*<<< orphan*/  name; struct lochnagar_aif* priv; } ;
struct lochnagar_aif {unsigned int master_mask; int /*<<< orphan*/  ctrl_reg; } ;
struct TYPE_2__ {struct regmap* regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LN_FTYPE_AIF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int lochnagar_aif_set_master(struct lochnagar_pin_priv *priv,
				    unsigned int group_idx, bool master)
{
	struct regmap *regmap = priv->lochnagar->regmap;
	const struct lochnagar_group *group = &priv->groups[group_idx];
	const struct lochnagar_aif *aif = group->priv;
	unsigned int val = 0;
	int ret;

	if (group->type != LN_FTYPE_AIF)
		return -EINVAL;

	if (!master)
		val = aif->master_mask;

	dev_dbg(priv->dev, "Set AIF %s to %s\n",
		group->name, master ? "master" : "slave");

	ret = regmap_update_bits(regmap, aif->ctrl_reg, aif->master_mask, val);
	if (ret) {
		dev_err(priv->dev, "Failed to set %s mode: %d\n",
			group->name, ret);
		return ret;
	}

	return 0;
}