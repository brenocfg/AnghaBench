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
struct st_retime_packed {int /*<<< orphan*/  delay_1; int /*<<< orphan*/  delay_0; int /*<<< orphan*/  retime; int /*<<< orphan*/  invertclk; int /*<<< orphan*/  double_edge; int /*<<< orphan*/  clknotdata; int /*<<< orphan*/  clk1notclk0; } ;
struct TYPE_2__ {struct st_retime_packed rt_p; } ;
struct st_pio_control {TYPE_1__ rt; } ;
struct st_pinctrl {struct st_pctl_data* data; } ;
struct st_pctl_data {int dummy; } ;

/* Variables and functions */
 unsigned int ST_PINCONF_UNPACK_RT (unsigned long) ; 
 unsigned int ST_PINCONF_UNPACK_RT_CLK (unsigned long) ; 
 unsigned int ST_PINCONF_UNPACK_RT_CLKNOTDATA (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_UNPACK_RT_DELAY (unsigned long) ; 
 unsigned int ST_PINCONF_UNPACK_RT_DOUBLE_EDGE (unsigned long) ; 
 unsigned int ST_PINCONF_UNPACK_RT_INVERTCLK (unsigned long) ; 
 unsigned int st_pinconf_delay_to_bit (int /*<<< orphan*/ ,struct st_pctl_data const*,unsigned long) ; 
 int /*<<< orphan*/  st_regmap_field_bit_set_clear_pin (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void st_pinconf_set_retime_packed(struct st_pinctrl *info,
	struct st_pio_control *pc,	unsigned long config, int pin)
{
	const struct st_pctl_data *data = info->data;
	struct st_retime_packed *rt_p = &pc->rt.rt_p;
	unsigned int delay;

	st_regmap_field_bit_set_clear_pin(rt_p->clk1notclk0,
				ST_PINCONF_UNPACK_RT_CLK(config), pin);

	st_regmap_field_bit_set_clear_pin(rt_p->clknotdata,
				ST_PINCONF_UNPACK_RT_CLKNOTDATA(config), pin);

	st_regmap_field_bit_set_clear_pin(rt_p->double_edge,
				ST_PINCONF_UNPACK_RT_DOUBLE_EDGE(config), pin);

	st_regmap_field_bit_set_clear_pin(rt_p->invertclk,
				ST_PINCONF_UNPACK_RT_INVERTCLK(config), pin);

	st_regmap_field_bit_set_clear_pin(rt_p->retime,
				ST_PINCONF_UNPACK_RT(config), pin);

	delay = st_pinconf_delay_to_bit(ST_PINCONF_UNPACK_RT_DELAY(config),
					data, config);
	/* 2 bit delay, lsb */
	st_regmap_field_bit_set_clear_pin(rt_p->delay_0, delay & 0x1, pin);
	/* 2 bit delay, msb */
	st_regmap_field_bit_set_clear_pin(rt_p->delay_1, delay & 0x2, pin);

}