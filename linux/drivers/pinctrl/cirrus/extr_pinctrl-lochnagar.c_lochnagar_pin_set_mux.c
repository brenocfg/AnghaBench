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
struct lochnagar_pin_priv {int /*<<< orphan*/  dev; TYPE_1__* lochnagar; } ;
struct lochnagar_pin {int /*<<< orphan*/  name; int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  LOCHNAGAR1 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int lochnagar2_get_gpio_chan (struct lochnagar_pin_priv*,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int lochnagar_pin_set_mux(struct lochnagar_pin_priv *priv,
				 const struct lochnagar_pin *pin,
				 unsigned int op)
{
	int ret;

	switch (priv->lochnagar->type) {
	case LOCHNAGAR1:
		break;
	default:
		ret = lochnagar2_get_gpio_chan(priv, op);
		if (ret < 0) {
			dev_err(priv->dev, "Failed to get channel for %s: %d\n",
				pin->name, ret);
			return ret;
		}

		op = ret;
		break;
	}

	dev_dbg(priv->dev, "Set pin %s to 0x%x\n", pin->name, op);

	ret = regmap_write(priv->lochnagar->regmap, pin->reg, op);
	if (ret)
		dev_err(priv->dev, "Failed to set %s mux: %d\n",
			pin->name, ret);

	return 0;
}