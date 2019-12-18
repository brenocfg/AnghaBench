#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct lochnagar_pin_priv {int /*<<< orphan*/  dev; TYPE_2__* pins; TYPE_1__* lochnagar; } ;
struct lochnagar_pin {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  reg; } ;
struct lochnagar_group {int npins; size_t* pins; int /*<<< orphan*/  name; struct lochnagar_aif* priv; } ;
struct lochnagar_aif {unsigned int src_mask; unsigned int ena_mask; int /*<<< orphan*/  ctrl_reg; int /*<<< orphan*/  src_reg; } ;
struct TYPE_4__ {struct lochnagar_pin* drv_data; } ;
struct TYPE_3__ {struct regmap* regmap; } ;

/* Variables and functions */
 unsigned int LN2_OP_AIF ; 
 scalar_t__ LN_PTYPE_MUX ; 
 unsigned int LOCHNAGAR2_GPIO_SRC_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int lochnagar_aif_set_mux(struct lochnagar_pin_priv *priv,
				 const struct lochnagar_group *group,
				 unsigned int op)
{
	struct regmap *regmap = priv->lochnagar->regmap;
	const struct lochnagar_aif *aif = group->priv;
	const struct lochnagar_pin *pin;
	int i, ret;

	ret = regmap_update_bits(regmap, aif->src_reg, aif->src_mask, op);
	if (ret) {
		dev_err(priv->dev, "Failed to set %s source: %d\n",
			group->name, ret);
		return ret;
	}

	ret = regmap_update_bits(regmap, aif->ctrl_reg,
				 aif->ena_mask, aif->ena_mask);
	if (ret) {
		dev_err(priv->dev, "Failed to set %s enable: %d\n",
			group->name, ret);
		return ret;
	}

	for (i = 0; i < group->npins; i++) {
		pin = priv->pins[group->pins[i]].drv_data;

		if (pin->type != LN_PTYPE_MUX)
			continue;

		dev_dbg(priv->dev, "Set pin %s to AIF\n", pin->name);

		ret = regmap_update_bits(regmap, pin->reg,
					 LOCHNAGAR2_GPIO_SRC_MASK,
					 LN2_OP_AIF);
		if (ret) {
			dev_err(priv->dev, "Failed to set %s to AIF: %d\n",
				pin->name, ret);
			return ret;
		}
	}

	return 0;
}