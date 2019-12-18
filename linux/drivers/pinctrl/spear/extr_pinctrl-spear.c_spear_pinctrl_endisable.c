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
struct spear_pmx {int /*<<< orphan*/  dev; TYPE_1__* machdata; } ;
struct spear_pingroup {int nmodemuxs; int /*<<< orphan*/  name; struct spear_modemux* modemuxs; } ;
struct spear_modemux {int modes; int /*<<< orphan*/  nmuxregs; int /*<<< orphan*/  muxregs; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int mode; scalar_t__ modes_supported; struct spear_pingroup** groups; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  muxregs_endisable (struct spear_pmx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct spear_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int spear_pinctrl_endisable(struct pinctrl_dev *pctldev,
		unsigned function, unsigned group, bool enable)
{
	struct spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	const struct spear_pingroup *pgroup;
	const struct spear_modemux *modemux;
	int i;
	bool found = false;

	pgroup = pmx->machdata->groups[group];

	for (i = 0; i < pgroup->nmodemuxs; i++) {
		modemux = &pgroup->modemuxs[i];

		/* SoC have any modes */
		if (pmx->machdata->modes_supported) {
			if (!(pmx->machdata->mode & modemux->modes))
				continue;
		}

		found = true;
		muxregs_endisable(pmx, modemux->muxregs, modemux->nmuxregs,
				enable);
	}

	if (!found) {
		dev_err(pmx->dev, "pinmux group: %s not supported\n",
				pgroup->name);
		return -ENODEV;
	}

	return 0;
}