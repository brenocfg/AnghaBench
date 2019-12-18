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
typedef  int u32 ;
typedef  int u16 ;
struct tegra_pmx {TYPE_1__* soc; } ;
struct tegra_pingroup {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
typedef  int s8 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum tegra_pinconf_param { ____Placeholder_tegra_pinconf_param } tegra_pinconf_param ;
struct TYPE_2__ {struct tegra_pingroup* groups; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int TEGRA_PINCONF_PARAM_LOCK ; 
 int TEGRA_PINCONF_UNPACK_ARG (unsigned long) ; 
 int TEGRA_PINCONF_UNPACK_PARAM (unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct tegra_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int pmx_readl (struct tegra_pmx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmx_writel (struct tegra_pmx*,int,int,int /*<<< orphan*/ ) ; 
 int tegra_pinconf_reg (struct tegra_pmx*,struct tegra_pingroup const*,int,int,int*,int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static int tegra_pinconf_group_set(struct pinctrl_dev *pctldev,
				   unsigned group, unsigned long *configs,
				   unsigned num_configs)
{
	struct tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	enum tegra_pinconf_param param;
	u16 arg;
	const struct tegra_pingroup *g;
	int ret, i;
	s8 bank, bit, width;
	s32 reg;
	u32 val, mask;

	g = &pmx->soc->groups[group];

	for (i = 0; i < num_configs; i++) {
		param = TEGRA_PINCONF_UNPACK_PARAM(configs[i]);
		arg = TEGRA_PINCONF_UNPACK_ARG(configs[i]);

		ret = tegra_pinconf_reg(pmx, g, param, true, &bank, &reg, &bit,
					&width);
		if (ret < 0)
			return ret;

		val = pmx_readl(pmx, bank, reg);

		/* LOCK can't be cleared */
		if (param == TEGRA_PINCONF_PARAM_LOCK) {
			if ((val & BIT(bit)) && !arg) {
				dev_err(pctldev->dev, "LOCK bit cannot be cleared\n");
				return -EINVAL;
			}
		}

		/* Special-case Boolean values; allow any non-zero as true */
		if (width == 1)
			arg = !!arg;

		/* Range-check user-supplied value */
		mask = (1 << width) - 1;
		if (arg & ~mask) {
			dev_err(pctldev->dev,
				"config %lx: %x too big for %d bit register\n",
				configs[i], arg, width);
			return -EINVAL;
		}

		/* Update register */
		val &= ~(mask << bit);
		val |= arg << bit;
		pmx_writel(pmx, val, bank, reg);
	} /* for each config */

	return 0;
}