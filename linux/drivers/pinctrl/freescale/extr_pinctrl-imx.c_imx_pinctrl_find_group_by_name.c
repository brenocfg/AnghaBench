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
struct pinctrl_dev {int num_groups; } ;
struct group_desc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct group_desc* pinctrl_generic_get_group (struct pinctrl_dev*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline const struct group_desc *imx_pinctrl_find_group_by_name(
				struct pinctrl_dev *pctldev,
				const char *name)
{
	const struct group_desc *grp = NULL;
	int i;

	for (i = 0; i < pctldev->num_groups; i++) {
		grp = pinctrl_generic_get_group(pctldev, i);
		if (grp && !strcmp(grp->name, name))
			break;
	}

	return grp;
}