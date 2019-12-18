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
struct uniphier_pinctrl_priv {int /*<<< orphan*/  regmap; TYPE_1__* socdata; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int caps; } ;

/* Variables and functions */
 int UNIPHIER_PINCTRL_CAPS_DBGMUX_SEPARATE ; 
 int /*<<< orphan*/  UNIPHIER_PINCTRL_LOAD_PINMUX ; 
 unsigned int UNIPHIER_PINCTRL_PINMUX_BASE ; 
 struct uniphier_pinctrl_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int uniphier_conf_pin_input_enable (struct pinctrl_dev*,unsigned int,int) ; 

__attribute__((used)) static int uniphier_pmx_set_one_mux(struct pinctrl_dev *pctldev, unsigned pin,
				    int muxval)
{
	struct uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	unsigned int mux_bits, reg_stride, reg, reg_end, shift, mask;
	bool load_pinctrl;
	int ret;

	/* some pins need input-enabling */
	ret = uniphier_conf_pin_input_enable(pctldev, pin, 1);
	if (ret)
		return ret;

	if (muxval < 0)
		return 0;	/* dedicated pin; nothing to do for pin-mux */

	if (priv->socdata->caps & UNIPHIER_PINCTRL_CAPS_DBGMUX_SEPARATE) {
		/*
		 *  Mode     reg_offset     bit_position
		 *  Normal    4 * n        shift+3:shift
		 *  Debug     4 * n        shift+7:shift+4
		 */
		mux_bits = 4;
		reg_stride = 8;
		load_pinctrl = true;
	} else {
		/*
		 *  Mode     reg_offset     bit_position
		 *  Normal    8 * n        shift+3:shift
		 *  Debug     8 * n + 4    shift+3:shift
		 */
		mux_bits = 8;
		reg_stride = 4;
		load_pinctrl = false;
	}

	reg = UNIPHIER_PINCTRL_PINMUX_BASE + pin * mux_bits / 32 * reg_stride;
	reg_end = reg + reg_stride;
	shift = pin * mux_bits % 32;
	mask = (1U << mux_bits) - 1;

	/*
	 * If reg_stride is greater than 4, the MSB of each pinsel shall be
	 * stored in the offset+4.
	 */
	for (; reg < reg_end; reg += 4) {
		ret = regmap_update_bits(priv->regmap, reg,
					 mask << shift, muxval << shift);
		if (ret)
			return ret;
		muxval >>= mux_bits;
	}

	if (load_pinctrl) {
		ret = regmap_write(priv->regmap,
				   UNIPHIER_PINCTRL_LOAD_PINMUX, 1);
		if (ret)
			return ret;
	}

	return 0;
}