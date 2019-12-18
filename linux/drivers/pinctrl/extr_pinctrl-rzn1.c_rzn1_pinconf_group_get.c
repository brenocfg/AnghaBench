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
struct rzn1_pinctrl {int /*<<< orphan*/  dev; struct rzn1_pin_group* groups; } ;
struct rzn1_pin_group {unsigned int npins; int /*<<< orphan*/ * pins; int /*<<< orphan*/  name; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct rzn1_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 scalar_t__ rzn1_pinconf_get (struct pinctrl_dev*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int rzn1_pinconf_group_get(struct pinctrl_dev *pctldev,
				  unsigned int selector,
				  unsigned long *config)
{
	struct rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	struct rzn1_pin_group *grp = &ipctl->groups[selector];
	unsigned long old = 0;
	unsigned int i;

	dev_dbg(ipctl->dev, "group get %s selector:%u\n", grp->name, selector);

	for (i = 0; i < grp->npins; i++) {
		if (rzn1_pinconf_get(pctldev, grp->pins[i], config))
			return -ENOTSUPP;

		/* configs do not match between two pins */
		if (i && (old != *config))
			return -ENOTSUPP;

		old = *config;
	}

	return 0;
}