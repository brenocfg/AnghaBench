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
struct pinmux_ops {int /*<<< orphan*/  (* free ) (struct pinctrl_dev*,int) ;int /*<<< orphan*/  (* gpio_disable_free ) (struct pinctrl_dev*,struct pinctrl_gpio_range*,int) ;} ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  owner; int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct pin_desc {char* gpio_owner; char* mux_owner; int /*<<< orphan*/ * mux_setting; scalar_t__ mux_usecount; } ;
struct TYPE_2__ {struct pinmux_ops* pmxops; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct pin_desc* pin_desc_get (struct pinctrl_dev*,int) ; 
 int /*<<< orphan*/  stub1 (struct pinctrl_dev*,struct pinctrl_gpio_range*,int) ; 
 int /*<<< orphan*/  stub2 (struct pinctrl_dev*,int) ; 

__attribute__((used)) static const char *pin_free(struct pinctrl_dev *pctldev, int pin,
			    struct pinctrl_gpio_range *gpio_range)
{
	const struct pinmux_ops *ops = pctldev->desc->pmxops;
	struct pin_desc *desc;
	const char *owner;

	desc = pin_desc_get(pctldev, pin);
	if (desc == NULL) {
		dev_err(pctldev->dev,
			"pin is not registered so it cannot be freed\n");
		return NULL;
	}

	if (!gpio_range) {
		/*
		 * A pin should not be freed more times than allocated.
		 */
		if (WARN_ON(!desc->mux_usecount))
			return NULL;
		desc->mux_usecount--;
		if (desc->mux_usecount)
			return NULL;
	}

	/*
	 * If there is no kind of request function for the pin we just assume
	 * we got it by default and proceed.
	 */
	if (gpio_range && ops->gpio_disable_free)
		ops->gpio_disable_free(pctldev, gpio_range, pin);
	else if (ops->free)
		ops->free(pctldev, pin);

	if (gpio_range) {
		owner = desc->gpio_owner;
		desc->gpio_owner = NULL;
	} else {
		owner = desc->mux_owner;
		desc->mux_owner = NULL;
		desc->mux_setting = NULL;
	}

	module_put(pctldev->owner);

	return owner;
}