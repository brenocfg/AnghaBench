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
typedef  int /*<<< orphan*/  u32 ;
struct pinctrl_dev {int dummy; } ;
struct ns_pinctrl {int /*<<< orphan*/  offset; int /*<<< orphan*/  regmap; TYPE_1__* groups; } ;
struct TYPE_2__ {int num_pins; int* pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 struct ns_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ns_pinctrl_set_mux(struct pinctrl_dev *pctrl_dev,
			      unsigned int func_select,
			      unsigned int grp_select)
{
	struct ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	u32 unset = 0;
	u32 tmp;
	int i;

	for (i = 0; i < ns_pinctrl->groups[grp_select].num_pins; i++) {
		int pin_number = ns_pinctrl->groups[grp_select].pins[i];

		unset |= BIT(pin_number);
	}

	regmap_read(ns_pinctrl->regmap, ns_pinctrl->offset, &tmp);
	tmp &= ~unset;
	regmap_write(ns_pinctrl->regmap, ns_pinctrl->offset, tmp);

	return 0;
}