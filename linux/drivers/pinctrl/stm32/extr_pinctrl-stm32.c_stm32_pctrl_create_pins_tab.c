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
struct stm32_pinctrl {int pkg; int npins; TYPE_1__* match_data; } ;
struct stm32_desc_pin {int pkg; int /*<<< orphan*/  functions; int /*<<< orphan*/  pin; } ;
struct TYPE_2__ {int npins; struct stm32_desc_pin* pins; } ;

/* Variables and functions */

__attribute__((used)) static int stm32_pctrl_create_pins_tab(struct stm32_pinctrl *pctl,
				       struct stm32_desc_pin *pins)
{
	const struct stm32_desc_pin *p;
	int i, nb_pins_available = 0;

	for (i = 0; i < pctl->match_data->npins; i++) {
		p = pctl->match_data->pins + i;
		if (pctl->pkg && !(pctl->pkg & p->pkg))
			continue;
		pins->pin = p->pin;
		pins->functions = p->functions;
		pins++;
		nb_pins_available++;
	}

	pctl->npins = nb_pins_available;

	return 0;
}