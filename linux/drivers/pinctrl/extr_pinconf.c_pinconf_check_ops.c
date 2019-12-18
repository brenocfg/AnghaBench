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
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct pinconf_ops {int /*<<< orphan*/  pin_config_group_set; int /*<<< orphan*/  pin_config_set; } ;
struct TYPE_2__ {struct pinconf_ops* confops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

int pinconf_check_ops(struct pinctrl_dev *pctldev)
{
	const struct pinconf_ops *ops = pctldev->desc->confops;

	/* We have to be able to config the pins in SOME way */
	if (!ops->pin_config_set && !ops->pin_config_group_set) {
		dev_err(pctldev->dev,
			"pinconf has to be able to set a pins config\n");
		return -EINVAL;
	}
	return 0;
}