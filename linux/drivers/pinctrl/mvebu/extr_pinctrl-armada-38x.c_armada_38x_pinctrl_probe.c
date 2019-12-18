#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct mvebu_pinctrl_soc_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct mvebu_pinctrl_soc_info {unsigned int variant; int /*<<< orphan*/  nmodes; int /*<<< orphan*/  modes; void* ngpioranges; TYPE_2__* gpioranges; void* ncontrols; TYPE_2__* controls; } ;
struct TYPE_6__ {int /*<<< orphan*/  npins; } ;

/* Variables and functions */
 void* ARRAY_SIZE (TYPE_2__*) ; 
 int ENODEV ; 
 TYPE_2__* armada_38x_mpp_controls ; 
 TYPE_2__* armada_38x_mpp_gpio_ranges ; 
 int /*<<< orphan*/  armada_38x_mpp_modes ; 
 struct mvebu_pinctrl_soc_info armada_38x_pinctrl_info ; 
 int /*<<< orphan*/  armada_38x_pinctrl_of_match ; 
 int mvebu_pinctrl_simple_mmio_probe (struct platform_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int armada_38x_pinctrl_probe(struct platform_device *pdev)
{
	struct mvebu_pinctrl_soc_info *soc = &armada_38x_pinctrl_info;
	const struct of_device_id *match =
		of_match_device(armada_38x_pinctrl_of_match, &pdev->dev);

	if (!match)
		return -ENODEV;

	soc->variant = (unsigned) match->data & 0xff;
	soc->controls = armada_38x_mpp_controls;
	soc->ncontrols = ARRAY_SIZE(armada_38x_mpp_controls);
	soc->gpioranges = armada_38x_mpp_gpio_ranges;
	soc->ngpioranges = ARRAY_SIZE(armada_38x_mpp_gpio_ranges);
	soc->modes = armada_38x_mpp_modes;
	soc->nmodes = armada_38x_mpp_controls[0].npins;

	pdev->dev.platform_data = soc;

	return mvebu_pinctrl_simple_mmio_probe(pdev);
}