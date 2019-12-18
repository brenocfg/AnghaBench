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
struct pinctrl_gpio_range {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pctrl; } ;

/* Variables and functions */
 TYPE_1__ falcon_info ; 
 int /*<<< orphan*/  pinctrl_add_gpio_range (int /*<<< orphan*/ ,struct pinctrl_gpio_range*) ; 

void pinctrl_falcon_add_gpio_range(struct pinctrl_gpio_range *range)
{
	pinctrl_add_gpio_range(falcon_info.pctrl, range);
}