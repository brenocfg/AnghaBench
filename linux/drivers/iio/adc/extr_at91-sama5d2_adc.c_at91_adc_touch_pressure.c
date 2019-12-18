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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int x_pos; } ;
struct at91_adc_state {TYPE_1__ touch_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_PRESSR ; 
 int AT91_SAMA5D2_XYZ_MASK ; 
 int at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 at91_adc_touch_pressure(struct at91_adc_state *st)
{
	u32 val;
	u32 z1, z2;
	u32 pres;
	u32 rxp = 1;
	u32 factor = 1000;

	/* calculate the pressure */
	val = at91_adc_readl(st, AT91_SAMA5D2_PRESSR);
	z1 = val & AT91_SAMA5D2_XYZ_MASK;
	z2 = (val >> 16) & AT91_SAMA5D2_XYZ_MASK;

	if (z1 != 0)
		pres = rxp * (st->touch_st.x_pos * factor / 1024) *
			(z2 * factor / z1 - factor) /
			factor;
	else
		pres = 0xFFFF;       /* no pen contact */

	/*
	 * The pressure from device grows down, minimum is 0xFFFF, maximum 0x0.
	 * We compute it this way, but let's return it in the expected way,
	 * growing from 0 to 0xFFFF.
	 */
	return 0xFFFF - pres;
}