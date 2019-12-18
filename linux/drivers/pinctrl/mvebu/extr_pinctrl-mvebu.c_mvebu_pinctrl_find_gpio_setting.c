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
struct mvebu_pinctrl_group {unsigned int num_settings; struct mvebu_mpp_ctrl_setting* settings; } ;
struct mvebu_pinctrl {int variant; } ;
struct mvebu_mpp_ctrl_setting {int flags; int variant; } ;

/* Variables and functions */
 int MVEBU_SETTING_GPI ; 
 int MVEBU_SETTING_GPO ; 

__attribute__((used)) static struct mvebu_mpp_ctrl_setting *mvebu_pinctrl_find_gpio_setting(
	struct mvebu_pinctrl *pctl, struct mvebu_pinctrl_group *grp)
{
	unsigned n;
	for (n = 0; n < grp->num_settings; n++) {
		if (grp->settings[n].flags &
			(MVEBU_SETTING_GPO | MVEBU_SETTING_GPI)) {
			if (!pctl->variant || (pctl->variant &
						grp->settings[n].variant))
				return &grp->settings[n];
		}
	}
	return NULL;
}