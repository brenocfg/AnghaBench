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
struct pinctrl_pin_desc {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int pinctrl_register_one_pin (struct pinctrl_dev*,struct pinctrl_pin_desc const*) ; 

__attribute__((used)) static int pinctrl_register_pins(struct pinctrl_dev *pctldev,
				 const struct pinctrl_pin_desc *pins,
				 unsigned num_descs)
{
	unsigned i;
	int ret = 0;

	for (i = 0; i < num_descs; i++) {
		ret = pinctrl_register_one_pin(pctldev, &pins[i]);
		if (ret)
			return ret;
	}

	return 0;
}