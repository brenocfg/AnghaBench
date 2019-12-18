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
struct msm_pinctrl {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__ reserved_gpios; } ;

/* Variables and functions */
 scalar_t__ device_property_count_u16 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool msm_gpio_needs_valid_mask(struct msm_pinctrl *pctrl)
{
	if (pctrl->soc->reserved_gpios)
		return true;

	return device_property_count_u16(pctrl->dev, "gpios") > 0;
}