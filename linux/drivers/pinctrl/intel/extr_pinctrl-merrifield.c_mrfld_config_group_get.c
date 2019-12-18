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
 int mrfld_config_get (struct pinctrl_dev*,unsigned int const,unsigned long*) ; 
 int mrfld_get_group_pins (struct pinctrl_dev*,unsigned int,unsigned int const**,unsigned int*) ; 

__attribute__((used)) static int mrfld_config_group_get(struct pinctrl_dev *pctldev,
				  unsigned int group, unsigned long *config)
{
	const unsigned int *pins;
	unsigned int npins;
	int ret;

	ret = mrfld_get_group_pins(pctldev, group, &pins, &npins);
	if (ret)
		return ret;

	ret = mrfld_config_get(pctldev, pins[0], config);
	if (ret)
		return ret;

	return 0;
}