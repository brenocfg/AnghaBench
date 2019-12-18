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
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct cygnus_pinctrl {int /*<<< orphan*/  mux_log; struct cygnus_pin_group* groups; struct cygnus_pin_function* functions; } ;
struct TYPE_2__ {int /*<<< orphan*/  alt; int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; } ;
struct cygnus_pin_group {TYPE_1__ mux; int /*<<< orphan*/  name; } ;
struct cygnus_pin_function {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int cygnus_pinmux_set (struct cygnus_pinctrl*,struct cygnus_pin_function const*,struct cygnus_pin_group const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,unsigned int,...) ; 
 struct cygnus_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int cygnus_pinmux_set_mux(struct pinctrl_dev *pctrl_dev,
				 unsigned func_select, unsigned grp_select)
{
	struct cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	const struct cygnus_pin_function *func =
		&pinctrl->functions[func_select];
	const struct cygnus_pin_group *grp = &pinctrl->groups[grp_select];

	dev_dbg(pctrl_dev->dev, "func:%u name:%s grp:%u name:%s\n",
		func_select, func->name, grp_select, grp->name);

	dev_dbg(pctrl_dev->dev, "offset:0x%08x shift:%u alt:%u\n",
		grp->mux.offset, grp->mux.shift, grp->mux.alt);

	return cygnus_pinmux_set(pinctrl, func, grp, pinctrl->mux_log);
}