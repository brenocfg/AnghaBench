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
typedef  int u64 ;
typedef  int u32 ;
struct dsi_pll_output {int pll_vco_div_ref; int pll_vco_count; int pll_kvco_div_ref; int pll_kvco_count; int pll_misc1; int pll_resetsm_cntrl; int pll_resetsm_cntrl2; scalar_t__ pll_kvco_code; int /*<<< orphan*/  pll_resetsm_cntrl5; } ;
struct dsi_pll_input {int vco_measure_time; int kvco_measure_time; int bandgap_timer; int /*<<< orphan*/  pll_wakeup_timer; } ;
struct dsi_pll_14nm {int vco_current_rate; int vco_ref_clk_rate; struct dsi_pll_output out; struct dsi_pll_input in; } ;

/* Variables and functions */
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int pll_14nm_kvco_slop (int) ; 

__attribute__((used)) static void pll_14nm_calc_vco_count(struct dsi_pll_14nm *pll)
{
	struct dsi_pll_input *pin = &pll->in;
	struct dsi_pll_output *pout = &pll->out;
	u64 vco_clk_rate = pll->vco_current_rate;
	u64 fref = pll->vco_ref_clk_rate;
	u64 data;
	u32 cnt;

	data = fref * pin->vco_measure_time;
	do_div(data, 1000000);
	data &= 0x03ff;	/* 10 bits */
	data -= 2;
	pout->pll_vco_div_ref = data;

	data = div_u64(vco_clk_rate, 1000000);	/* unit is Mhz */
	data *= pin->vco_measure_time;
	do_div(data, 10);
	pout->pll_vco_count = data;

	data = fref * pin->kvco_measure_time;
	do_div(data, 1000000);
	data &= 0x03ff;	/* 10 bits */
	data -= 1;
	pout->pll_kvco_div_ref = data;

	cnt = pll_14nm_kvco_slop(vco_clk_rate);
	cnt *= 2;
	cnt /= 100;
	cnt *= pin->kvco_measure_time;
	pout->pll_kvco_count = cnt;

	pout->pll_misc1 = 16;
	pout->pll_resetsm_cntrl = 48;
	pout->pll_resetsm_cntrl2 = pin->bandgap_timer << 3;
	pout->pll_resetsm_cntrl5 = pin->pll_wakeup_timer;
	pout->pll_kvco_code = 0;
}