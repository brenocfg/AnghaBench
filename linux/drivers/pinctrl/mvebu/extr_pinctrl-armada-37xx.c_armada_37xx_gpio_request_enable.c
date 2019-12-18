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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct armada_37xx_pinctrl {int /*<<< orphan*/  dev; } ;
struct armada_37xx_pin_group {int dummy; } ;

/* Variables and functions */
 struct armada_37xx_pin_group* armada_37xx_find_next_grp_by_pin (struct armada_37xx_pinctrl*,unsigned int,int*) ; 
 int /*<<< orphan*/  armada_37xx_pmx_set_by_name (struct pinctrl_dev*,char*,struct armada_37xx_pin_group*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct armada_37xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int armada_37xx_gpio_request_enable(struct pinctrl_dev *pctldev,
					   struct pinctrl_gpio_range *range,
					   unsigned int offset)
{
	struct armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	struct armada_37xx_pin_group *group;
	int grp = 0;

	dev_dbg(info->dev, "requesting gpio %d\n", offset);

	while ((group = armada_37xx_find_next_grp_by_pin(info, offset, &grp)))
		armada_37xx_pmx_set_by_name(pctldev, "gpio", group);

	return 0;
}