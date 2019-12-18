#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {int ssc_period; int ssc_step_size; } ;
struct TYPE_3__ {int ssc_freq; int ssc_spread; int ssc_adj_period; } ;
struct dsi_pll_14nm {int vco_ref_clk_rate; TYPE_2__ out; TYPE_1__ in; scalar_t__ vco_current_rate; } ;

/* Variables and functions */
 int CEIL (int,int) ; 
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int div_u64 (int,int) ; 
 int div_u64_rem (int,int,int*) ; 

__attribute__((used)) static void pll_14nm_ssc_calc(struct dsi_pll_14nm *pll)
{
	u32 period, ssc_period;
	u32 ref, rem;
	u64 step_size;

	DBG("vco=%lld ref=%lld", pll->vco_current_rate, pll->vco_ref_clk_rate);

	ssc_period = pll->in.ssc_freq / 500;
	period = (u32)pll->vco_ref_clk_rate / 1000;
	ssc_period  = CEIL(period, ssc_period);
	ssc_period -= 1;
	pll->out.ssc_period = ssc_period;

	DBG("ssc freq=%d spread=%d period=%d", pll->in.ssc_freq,
	    pll->in.ssc_spread, pll->out.ssc_period);

	step_size = (u32)pll->vco_current_rate;
	ref = pll->vco_ref_clk_rate;
	ref /= 1000;
	step_size = div_u64(step_size, ref);
	step_size <<= 20;
	step_size = div_u64(step_size, 1000);
	step_size *= pll->in.ssc_spread;
	step_size = div_u64(step_size, 1000);
	step_size *= (pll->in.ssc_adj_period + 1);

	rem = 0;
	step_size = div_u64_rem(step_size, ssc_period + 1, &rem);
	if (rem)
		step_size++;

	DBG("step_size=%lld", step_size);

	step_size &= 0x0ffff;	/* take lower 16 bits */

	pll->out.ssc_step_size = step_size;
}