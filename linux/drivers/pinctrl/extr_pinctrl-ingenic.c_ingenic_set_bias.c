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
struct ingenic_pinctrl {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ID_JZ4760 ; 
 int /*<<< orphan*/  JZ4740_GPIO_PULL_DIS ; 
 int /*<<< orphan*/  JZ4760_GPIO_PEN ; 
 int /*<<< orphan*/  ingenic_config_pin (struct ingenic_pinctrl*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ingenic_set_bias(struct ingenic_pinctrl *jzpc,
		unsigned int pin, bool enabled)
{
	if (jzpc->version >= ID_JZ4760)
		ingenic_config_pin(jzpc, pin, JZ4760_GPIO_PEN, !enabled);
	else
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_PULL_DIS, !enabled);
}