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
struct rzn1_pinctrl {TYPE_1__* functions; int /*<<< orphan*/  dev; struct rzn1_pin_group* groups; } ;
struct rzn1_pin_group {unsigned int npins; int /*<<< orphan*/ * pin_ids; int /*<<< orphan*/ * pins; int /*<<< orphan*/  name; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_ALL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 struct rzn1_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  rzn1_hw_set_lock (struct rzn1_pinctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rzn1_set_hw_pin_func (struct rzn1_pinctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rzn1_set_mux(struct pinctrl_dev *pctldev, unsigned int selector,
			unsigned int group)
{
	struct rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	struct rzn1_pin_group *grp = &ipctl->groups[group];
	unsigned int i, grp_pins = grp->npins;

	dev_dbg(ipctl->dev, "set mux %s(%d) group %s(%d)\n",
		ipctl->functions[selector].name, selector, grp->name, group);

	rzn1_hw_set_lock(ipctl, LOCK_ALL, LOCK_ALL);
	for (i = 0; i < grp_pins; i++)
		rzn1_set_hw_pin_func(ipctl, grp->pins[i], grp->pin_ids[i], 0);
	rzn1_hw_set_lock(ipctl, LOCK_ALL, 0);

	return 0;
}