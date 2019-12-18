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
struct intel_pinctrl {int /*<<< orphan*/  dev; int /*<<< orphan*/  chip; } ;
struct intel_padgroup {scalar_t__ gpio_base; int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct intel_community {int ngpps; struct intel_padgroup* gpps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int gpiochip_add_pin_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_gpio_add_pin_ranges(struct intel_pinctrl *pctrl,
				     const struct intel_community *community)
{
	int ret = 0, i;

	for (i = 0; i < community->ngpps; i++) {
		const struct intel_padgroup *gpp = &community->gpps[i];

		if (gpp->gpio_base < 0)
			continue;

		ret = gpiochip_add_pin_range(&pctrl->chip, dev_name(pctrl->dev),
					     gpp->gpio_base, gpp->base,
					     gpp->size);
		if (ret)
			return ret;
	}

	return ret;
}