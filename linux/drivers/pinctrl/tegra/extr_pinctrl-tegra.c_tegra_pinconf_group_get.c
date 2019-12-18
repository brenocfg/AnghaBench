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
struct pinctrl_dev {int dummy; } ;
typedef  int s8 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum tegra_pinconf_param { ____Placeholder_tegra_pinconf_param } tegra_pinconf_param ;
struct TYPE_2__ {struct tegra_pingroup* groups; } ;

/* Variables and functions */
 unsigned long TEGRA_PINCONF_PACK (int,int) ; 
 int TEGRA_PINCONF_UNPACK_PARAM (unsigned long) ; 
 struct tegra_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int pmx_readl (struct tegra_pmx*,int,int /*<<< orphan*/ ) ; 
 int tegra_pinconf_reg (struct tegra_pmx*,struct tegra_pingroup const*,int,int,int*,int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static int tegra_pinconf_group_get(struct pinctrl_dev *pctldev,
				   unsigned group, unsigned long *config)
{
	struct tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	enum tegra_pinconf_param param = TEGRA_PINCONF_UNPACK_PARAM(*config);
	u16 arg;
	const struct tegra_pingroup *g;
	int ret;
	s8 bank, bit, width;
	s32 reg;
	u32 val, mask;

	g = &pmx->soc->groups[group];

	ret = tegra_pinconf_reg(pmx, g, param, true, &bank, &reg, &bit,
				&width);
	if (ret < 0)
		return ret;

	val = pmx_readl(pmx, bank, reg);
	mask = (1 << width) - 1;
	arg = (val >> bit) & mask;

	*config = TEGRA_PINCONF_PACK(param, arg);

	return 0;
}