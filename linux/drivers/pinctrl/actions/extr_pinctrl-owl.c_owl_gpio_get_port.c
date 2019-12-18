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
struct owl_pinctrl {TYPE_1__* soc; } ;
struct owl_gpio_port {unsigned int pins; } ;
struct TYPE_2__ {unsigned int nports; struct owl_gpio_port* ports; } ;

/* Variables and functions */

__attribute__((used)) static const struct owl_gpio_port *
owl_gpio_get_port(struct owl_pinctrl *pctrl, unsigned int *pin)
{
	unsigned int start = 0, i;

	for (i = 0; i < pctrl->soc->nports; i++) {
		const struct owl_gpio_port *port = &pctrl->soc->ports[i];

		if (*pin >= start && *pin < start + port->pins) {
			*pin -= start;
			return port;
		}

		start += port->pins;
	}

	return NULL;
}