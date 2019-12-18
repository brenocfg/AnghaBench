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
struct at91_pinctrl {int ngroups; int /*<<< orphan*/  dev; struct at91_pin_group* groups; } ;
struct at91_pin_group {int /*<<< orphan*/ * pins; int /*<<< orphan*/  npins; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline const struct at91_pin_group *at91_pinctrl_find_group_by_name(
				const struct at91_pinctrl *info,
				const char *name)
{
	const struct at91_pin_group *grp = NULL;
	int i;

	for (i = 0; i < info->ngroups; i++) {
		if (strcmp(info->groups[i].name, name))
			continue;

		grp = &info->groups[i];
		dev_dbg(info->dev, "%s: %d 0:%d\n", name, grp->npins, grp->pins[0]);
		break;
	}

	return grp;
}