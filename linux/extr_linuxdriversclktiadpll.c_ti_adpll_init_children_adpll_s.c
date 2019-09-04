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
struct ti_adpll_data {scalar_t__ regs; TYPE_2__* clocks; scalar_t__* parent_clocks; TYPE_1__* c; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_type_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADPLL_CLKCTRL_CLKOUTEN ; 
 scalar_t__ ADPLL_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  ADPLL_CLKCTRL_ULOWCLKEN ; 
 int /*<<< orphan*/  ADPLL_CLKINPHIFSEL_ADPLL_S ; 
 int /*<<< orphan*/  ADPLL_M2NDIV_M2 ; 
 int /*<<< orphan*/  ADPLL_M2NDIV_M2_ADPLL_S_WIDTH ; 
 scalar_t__ ADPLL_M2NDIV_OFFSET ; 
 int /*<<< orphan*/  ADPLL_M3DIV_M3 ; 
 int /*<<< orphan*/  ADPLL_M3DIV_M3_WIDTH ; 
 scalar_t__ ADPLL_M3DIV_OFFSET ; 
 int /*<<< orphan*/  CLK_DIVIDER_ONE_BASED ; 
 int /*<<< orphan*/  ENODEV ; 
 size_t TI_ADPLL_BYPASS ; 
 size_t TI_ADPLL_CLKINPHIF ; 
 size_t TI_ADPLL_CLKINPULOW ; 
 int /*<<< orphan*/  TI_ADPLL_CLKOUT ; 
 int /*<<< orphan*/  TI_ADPLL_CLKOUT2 ; 
 size_t TI_ADPLL_DCO ; 
 size_t TI_ADPLL_DIV2 ; 
 size_t TI_ADPLL_HIF ; 
 size_t TI_ADPLL_M2 ; 
 size_t TI_ADPLL_M3 ; 
 size_t TI_ADPLL_N2 ; 
 int /*<<< orphan*/  TI_ADPLL_S_CLKOUT ; 
 int /*<<< orphan*/  TI_ADPLL_S_CLKOUTHIF ; 
 int /*<<< orphan*/  TI_ADPLL_S_CLKOUTX2 ; 
 int ti_adpll_init_clkout (struct ti_adpll_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ti_adpll_init_divider (struct ti_adpll_data*,size_t,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ti_adpll_init_fixed_factor (struct ti_adpll_data*,size_t,char*,int /*<<< orphan*/ ,int,int) ; 
 int ti_adpll_init_mux (struct ti_adpll_data*,size_t,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_adpll_init_children_adpll_s(struct ti_adpll_data *d)
{
	int err;

	if (!d->c->is_type_s)
		return 0;

	/* Internal mux, sources from divider N2 or clkinpulow */
	err = ti_adpll_init_mux(d, TI_ADPLL_BYPASS, "bypass",
				d->clocks[TI_ADPLL_N2].clk,
				d->parent_clocks[TI_ADPLL_CLKINPULOW],
				d->regs + ADPLL_CLKCTRL_OFFSET,
				ADPLL_CLKCTRL_ULOWCLKEN);
	if (err)
		return err;

	/* Internal divider M2, sources DCO */
	err = ti_adpll_init_divider(d, TI_ADPLL_M2, -ENODEV, "m2",
				    d->clocks[TI_ADPLL_DCO].clk,
				    d->regs + ADPLL_M2NDIV_OFFSET,
				    ADPLL_M2NDIV_M2,
				    ADPLL_M2NDIV_M2_ADPLL_S_WIDTH,
				    CLK_DIVIDER_ONE_BASED);
	if (err)
		return err;

	/* Internal fixed divider, after M2 before clkout */
	err = ti_adpll_init_fixed_factor(d, TI_ADPLL_DIV2, "div2",
					 d->clocks[TI_ADPLL_M2].clk,
					 1, 2);
	if (err)
		return err;

	/* Output clkout with a mux and gate, sources from div2 or bypass */
	err = ti_adpll_init_clkout(d, TI_ADPLL_CLKOUT, TI_ADPLL_S_CLKOUT,
				   ADPLL_CLKCTRL_CLKOUTEN, "clkout",
				   d->clocks[TI_ADPLL_DIV2].clk,
				   d->clocks[TI_ADPLL_BYPASS].clk);
	if (err)
		return err;

	/* Output clkoutx2 with a mux and gate, sources from M2 or bypass */
	err = ti_adpll_init_clkout(d, TI_ADPLL_CLKOUT2, TI_ADPLL_S_CLKOUTX2, 0,
				   "clkout2", d->clocks[TI_ADPLL_M2].clk,
				   d->clocks[TI_ADPLL_BYPASS].clk);
	if (err)
		return err;

	/* Internal mux, sources from DCO and clkinphif */
	if (d->parent_clocks[TI_ADPLL_CLKINPHIF]) {
		err = ti_adpll_init_mux(d, TI_ADPLL_HIF, "hif",
					d->clocks[TI_ADPLL_DCO].clk,
					d->parent_clocks[TI_ADPLL_CLKINPHIF],
					d->regs + ADPLL_CLKCTRL_OFFSET,
					ADPLL_CLKINPHIFSEL_ADPLL_S);
		if (err)
			return err;
	}

	/* Output clkouthif with a divider M3, sources from hif */
	err = ti_adpll_init_divider(d, TI_ADPLL_M3, TI_ADPLL_S_CLKOUTHIF, "m3",
				    d->clocks[TI_ADPLL_HIF].clk,
				    d->regs + ADPLL_M3DIV_OFFSET,
				    ADPLL_M3DIV_M3,
				    ADPLL_M3DIV_M3_WIDTH,
				    CLK_DIVIDER_ONE_BASED);
	if (err)
		return err;

	/* Output clock dcoclkldo is the DCO */

	return 0;
}