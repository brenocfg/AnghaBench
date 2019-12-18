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
typedef  int /*<<< orphan*/  supply ;
struct sunxi_pinctrl_regulator {struct regulator* regulator; int /*<<< orphan*/  refcount; } ;
struct sunxi_pinctrl {int /*<<< orphan*/  dev; struct sunxi_pinctrl_regulator* regulators; TYPE_1__* desc; } ;
struct regulator {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {unsigned int pin_base; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator*) ; 
 unsigned int PINS_PER_BANK ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char) ; 
 struct sunxi_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int regulator_enable (struct regulator*) ; 
 struct regulator* regulator_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regulator_put (struct regulator*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char) ; 
 int /*<<< orphan*/  sunxi_pinctrl_set_io_bias_cfg (struct sunxi_pinctrl*,unsigned int,struct regulator*) ; 

__attribute__((used)) static int sunxi_pmx_request(struct pinctrl_dev *pctldev, unsigned offset)
{
	struct sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	unsigned short bank = offset / PINS_PER_BANK;
	unsigned short bank_offset = bank - pctl->desc->pin_base /
					    PINS_PER_BANK;
	struct sunxi_pinctrl_regulator *s_reg = &pctl->regulators[bank_offset];
	struct regulator *reg = s_reg->regulator;
	char supply[16];
	int ret;

	if (reg) {
		refcount_inc(&s_reg->refcount);
		return 0;
	}

	snprintf(supply, sizeof(supply), "vcc-p%c", 'a' + bank);
	reg = regulator_get(pctl->dev, supply);
	if (IS_ERR(reg)) {
		dev_err(pctl->dev, "Couldn't get bank P%c regulator\n",
			'A' + bank);
		return PTR_ERR(reg);
	}

	ret = regulator_enable(reg);
	if (ret) {
		dev_err(pctl->dev,
			"Couldn't enable bank P%c regulator\n", 'A' + bank);
		goto out;
	}

	sunxi_pinctrl_set_io_bias_cfg(pctl, offset, reg);

	s_reg->regulator = reg;
	refcount_set(&s_reg->refcount, 1);

	return 0;

out:
	regulator_put(s_reg->regulator);

	return ret;
}