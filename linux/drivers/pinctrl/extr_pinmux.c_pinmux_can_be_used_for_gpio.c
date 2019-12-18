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
struct pinmux_ops {scalar_t__ strict; } ;
struct pinctrl_dev {TYPE_1__* desc; } ;
struct pin_desc {int /*<<< orphan*/  gpio_owner; scalar_t__ mux_usecount; } ;
struct TYPE_2__ {struct pinmux_ops* pmxops; } ;

/* Variables and functions */
 struct pin_desc* pin_desc_get (struct pinctrl_dev*,unsigned int) ; 

bool pinmux_can_be_used_for_gpio(struct pinctrl_dev *pctldev, unsigned pin)
{
	struct pin_desc *desc = pin_desc_get(pctldev, pin);
	const struct pinmux_ops *ops = pctldev->desc->pmxops;

	/* Can't inspect pin, assume it can be used */
	if (!desc)
		return true;

	if (ops->strict && desc->mux_usecount)
		return false;

	return !(ops->strict && !!desc->gpio_owner);
}