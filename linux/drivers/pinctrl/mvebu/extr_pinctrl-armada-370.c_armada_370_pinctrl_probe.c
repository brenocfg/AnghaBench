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
struct TYPE_2__ {struct mvebu_pinctrl_soc_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mvebu_pinctrl_soc_info {void* ngpioranges; void* gpioranges; void* nmodes; void* modes; void* ncontrols; void* controls; scalar_t__ variant; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 struct mvebu_pinctrl_soc_info armada_370_pinctrl_info ; 
 void* mv88f6710_mpp_controls ; 
 void* mv88f6710_mpp_gpio_ranges ; 
 void* mv88f6710_mpp_modes ; 
 int mvebu_pinctrl_simple_mmio_probe (struct platform_device*) ; 

__attribute__((used)) static int armada_370_pinctrl_probe(struct platform_device *pdev)
{
	struct mvebu_pinctrl_soc_info *soc = &armada_370_pinctrl_info;

	soc->variant = 0; /* no variants for Armada 370 */
	soc->controls = mv88f6710_mpp_controls;
	soc->ncontrols = ARRAY_SIZE(mv88f6710_mpp_controls);
	soc->modes = mv88f6710_mpp_modes;
	soc->nmodes = ARRAY_SIZE(mv88f6710_mpp_modes);
	soc->gpioranges = mv88f6710_mpp_gpio_ranges;
	soc->ngpioranges = ARRAY_SIZE(mv88f6710_mpp_gpio_ranges);

	pdev->dev.platform_data = soc;

	return mvebu_pinctrl_simple_mmio_probe(pdev);
}