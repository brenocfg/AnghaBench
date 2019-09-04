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
struct stv090x_state {TYPE_1__* internal; struct stv090x_config* config; } ;
struct stv090x_config {int xtal; } ;
struct TYPE_2__ {int mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  F22RX ; 
 int /*<<< orphan*/  F22TX ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  M_DIV_FIELD ; 
 int /*<<< orphan*/  SELX1RATIO_FIELD ; 
 int STV090x_GETFIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_NCOARSE ; 
 int /*<<< orphan*/  STV090x_SETFIELD (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STV090x_SYNTCTRL ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int stv090x_get_mclk (struct stv090x_state*) ; 
 int stv090x_read_reg (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stv090x_write_reg (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv090x_set_mclk(struct stv090x_state *state, u32 mclk, u32 clk)
{
	const struct stv090x_config *config = state->config;
	u32 reg, div, clk_sel;

	reg = stv090x_read_reg(state, STV090x_SYNTCTRL);
	clk_sel = ((STV090x_GETFIELD(reg, SELX1RATIO_FIELD) == 1) ? 4 : 6);

	div = ((clk_sel * mclk) / config->xtal) - 1;

	reg = stv090x_read_reg(state, STV090x_NCOARSE);
	STV090x_SETFIELD(reg, M_DIV_FIELD, div);
	if (stv090x_write_reg(state, STV090x_NCOARSE, reg) < 0)
		goto err;

	state->internal->mclk = stv090x_get_mclk(state);

	/*Set the DiseqC frequency to 22KHz */
	div = state->internal->mclk / 704000;
	if (STV090x_WRITE_DEMOD(state, F22TX, div) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, F22RX, div) < 0)
		goto err;

	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}