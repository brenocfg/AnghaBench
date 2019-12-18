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

/* Variables and functions */
 int samsung_pinconf_rw (struct pinctrl_dev*,unsigned int,unsigned long*,int) ; 

__attribute__((used)) static int samsung_pinconf_set(struct pinctrl_dev *pctldev, unsigned int pin,
				unsigned long *configs, unsigned num_configs)
{
	int i, ret;

	for (i = 0; i < num_configs; i++) {
		ret = samsung_pinconf_rw(pctldev, pin, &configs[i], true);
		if (ret < 0)
			return ret;
	} /* for each config */

	return 0;
}