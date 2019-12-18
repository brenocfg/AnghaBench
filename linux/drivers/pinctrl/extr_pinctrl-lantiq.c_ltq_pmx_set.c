#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct ltq_pinmux_info {int (* apply_mux ) (struct pinctrl_dev*,int,int) ;int /*<<< orphan*/  dev; int /*<<< orphan*/ * mfp; struct ltq_pin_group* grps; } ;
struct ltq_pin_group {int npins; int /*<<< orphan*/  mux; int /*<<< orphan*/ * pins; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ match_group_mux (struct ltq_pin_group const*,struct ltq_pinmux_info*,int /*<<< orphan*/ ) ; 
 int match_mfp (struct ltq_pinmux_info*,int /*<<< orphan*/ ) ; 
 int match_mux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ltq_pinmux_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int stub1 (struct pinctrl_dev*,int,int) ; 

__attribute__((used)) static int ltq_pmx_set(struct pinctrl_dev *pctrldev,
		       unsigned func,
		       unsigned group)
{
	struct ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	const struct ltq_pin_group *pin_grp = &info->grps[group];
	int i, pin, pin_func, ret;

	if (!pin_grp->npins ||
		(match_group_mux(pin_grp, info, pin_grp->mux) < 0)) {
		dev_err(info->dev, "Failed to set the pin group: %s\n",
			info->grps[group].name);
		return -EINVAL;
	}
	for (i = 0; i < pin_grp->npins; i++) {
		pin = match_mfp(info, pin_grp->pins[i]);
		if (pin < 0) {
			dev_err(info->dev, "could not find mfp for pin %d\n",
				pin_grp->pins[i]);
			return -EINVAL;
		}
		pin_func = match_mux(&info->mfp[pin], pin_grp->mux);
		ret = info->apply_mux(pctrldev, pin, pin_func);
		if (ret) {
			dev_err(info->dev,
				"failed to apply mux %d for pin %d\n",
				pin_func, pin);
			return ret;
		}
	}
	return 0;
}