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
struct mvebu_pinctrl_group {int /*<<< orphan*/  name; } ;
struct mvebu_pinctrl {unsigned int num_groups; struct mvebu_pinctrl_group* groups; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mvebu_pinctrl_group *mvebu_pinctrl_find_group_by_name(
	struct mvebu_pinctrl *pctl, const char *name)
{
	unsigned n;
	for (n = 0; n < pctl->num_groups; n++) {
		if (strcmp(name, pctl->groups[n].name) == 0)
			return &pctl->groups[n];
	}
	return NULL;
}