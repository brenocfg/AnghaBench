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
struct st_retime_dedicated {int /*<<< orphan*/ * rt; } ;
struct TYPE_2__ {struct st_retime_dedicated rt_d; } ;
struct st_pio_control {TYPE_1__ rt; } ;
struct st_pinctrl {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned int RT_D_CFG_CLKNOTDATA_MASK ; 
 unsigned int RT_D_CFG_CLK_MASK ; 
 unsigned int RT_D_CFG_CLK_SHIFT ; 
 unsigned int RT_D_CFG_DELAY_MASK ; 
 unsigned int RT_D_CFG_DELAY_SHIFT ; 
 unsigned int RT_D_CFG_DOUBLE_EDGE_MASK ; 
 unsigned int RT_D_CFG_INVERTCLK_MASK ; 
 unsigned int RT_D_CFG_RETIME_MASK ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_RT (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_RT_CLK (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_RT_CLKNOTDATA (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_RT_DELAY (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_RT_DOUBLE_EDGE (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_RT_INVERTCLK (unsigned long) ; 
 int ST_PINCONF_UNPACK_OE (unsigned long) ; 
 int /*<<< orphan*/  regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned long st_pinconf_bit_to_delay (unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int st_pinconf_get_retime_dedicated(struct st_pinctrl *info,
	struct st_pio_control *pc,	int pin, unsigned long *config)
{
	unsigned int value;
	unsigned long delay_bits, delay, rt_clk;
	int output = ST_PINCONF_UNPACK_OE(*config);
	struct st_retime_dedicated *rt_d = &pc->rt.rt_d;

	regmap_field_read(rt_d->rt[pin], &value);

	rt_clk = (value & RT_D_CFG_CLK_MASK) >> RT_D_CFG_CLK_SHIFT;
	ST_PINCONF_PACK_RT_CLK(*config, rt_clk);

	delay_bits = (value & RT_D_CFG_DELAY_MASK) >> RT_D_CFG_DELAY_SHIFT;
	delay =  st_pinconf_bit_to_delay(delay_bits, info->data, output);
	ST_PINCONF_PACK_RT_DELAY(*config, delay);

	if (value & RT_D_CFG_CLKNOTDATA_MASK)
		ST_PINCONF_PACK_RT_CLKNOTDATA(*config);

	if (value & RT_D_CFG_DOUBLE_EDGE_MASK)
		ST_PINCONF_PACK_RT_DOUBLE_EDGE(*config);

	if (value & RT_D_CFG_INVERTCLK_MASK)
		ST_PINCONF_PACK_RT_INVERTCLK(*config);

	if (value & RT_D_CFG_RETIME_MASK)
		ST_PINCONF_PACK_RT(*config);

	return 0;
}