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
struct pic32_pinctrl {int /*<<< orphan*/  dev; scalar_t__ reg_base; struct pic32_function* functions; struct pic32_pin_group* groups; } ;
struct pic32_pin_group {struct pic32_desc_function* functions; } ;
struct pic32_function {char* name; } ;
struct pic32_desc_function {scalar_t__ muxreg; int /*<<< orphan*/  muxval; scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct pic32_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pic32_pinmux_enable(struct pinctrl_dev *pctldev,
				   unsigned func, unsigned group)
{
	struct pic32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	const struct pic32_pin_group *pg = &pctl->groups[group];
	const struct pic32_function *pf = &pctl->functions[func];
	const char *fname = pf->name;
	struct pic32_desc_function *functions = pg->functions;

	while (functions->name) {
		if (!strcmp(functions->name, fname)) {
			dev_dbg(pctl->dev,
				"setting function %s reg 0x%x = %d\n",
				fname, functions->muxreg, functions->muxval);

			writel(functions->muxval, pctl->reg_base + functions->muxreg);

			return 0;
		}

		functions++;
	}

	dev_err(pctl->dev, "cannot mux pin %u to function %u\n", group, func);

	return -EINVAL;
}