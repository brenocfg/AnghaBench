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
struct sprd_pinctrl_soc_info {int npins; TYPE_1__* pins; } ;
struct sprd_pinctrl {struct sprd_pinctrl_soc_info* info; } ;
struct TYPE_2__ {int number; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int sprd_pinctrl_get_id_by_name(struct sprd_pinctrl *sprd_pctl,
				       const char *name)
{
	struct sprd_pinctrl_soc_info *info = sprd_pctl->info;
	int i;

	for (i = 0; i < info->npins; i++) {
		if (!strcmp(info->pins[i].name, name))
			return info->pins[i].number;
	}

	return -ENODEV;
}