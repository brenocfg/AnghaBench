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
struct pinctrl_gpio_range {int /*<<< orphan*/  name; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int pin_request (struct pinctrl_dev*,unsigned int,char const*,struct pinctrl_gpio_range*) ; 

int pinmux_request_gpio(struct pinctrl_dev *pctldev,
			struct pinctrl_gpio_range *range,
			unsigned pin, unsigned gpio)
{
	const char *owner;
	int ret;

	/* Conjure some name stating what chip and pin this is taken by */
	owner = kasprintf(GFP_KERNEL, "%s:%d", range->name, gpio);
	if (!owner)
		return -ENOMEM;

	ret = pin_request(pctldev, pin, owner, range);
	if (ret < 0)
		kfree(owner);

	return ret;
}