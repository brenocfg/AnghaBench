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
struct st_pio_control {int rt_pin_mask; } ;
struct st_pinctrl {TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ rt_style; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  st_pinconf_set_retime_dedicated (struct st_pinctrl*,struct st_pio_control*,unsigned long,int) ; 
 int /*<<< orphan*/  st_pinconf_set_retime_packed (struct st_pinctrl*,struct st_pio_control*,unsigned long,int) ; 
 scalar_t__ st_retime_style_dedicated ; 
 scalar_t__ st_retime_style_packed ; 

__attribute__((used)) static void st_pinconf_set_retime(struct st_pinctrl *info,
	struct st_pio_control *pc, int pin, unsigned long config)
{
	if (info->data->rt_style == st_retime_style_packed)
		st_pinconf_set_retime_packed(info, pc, config, pin);
	else if (info->data->rt_style == st_retime_style_dedicated)
		if ((BIT(pin) & pc->rt_pin_mask))
			st_pinconf_set_retime_dedicated(info, pc,
							config, pin);
}