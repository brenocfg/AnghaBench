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
typedef  int u32 ;
struct stv0367_state {int dummy; } ;
struct dvb_frontend {struct stv0367_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  F367CAB_BYPASS_PLLXN ; 
 int /*<<< orphan*/  F367CAB_PLL_MDIV ; 
 int /*<<< orphan*/  F367CAB_PLL_NDIV ; 
 int /*<<< orphan*/  F367CAB_PLL_PDIV ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 scalar_t__ stv0367_readbits (struct stv0367_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stv0367cab_get_mclk(struct dvb_frontend *fe, u32 ExtClk_Hz)
{
	struct stv0367_state *state = fe->demodulator_priv;
	u32 mclk_Hz = 0;/* master clock frequency (Hz) */
	u32 M, N, P;


	if (stv0367_readbits(state, F367CAB_BYPASS_PLLXN) == 0) {
		N = (u32)stv0367_readbits(state, F367CAB_PLL_NDIV);
		if (N == 0)
			N = N + 1;

		M = (u32)stv0367_readbits(state, F367CAB_PLL_MDIV);
		if (M == 0)
			M = M + 1;

		P = (u32)stv0367_readbits(state, F367CAB_PLL_PDIV);

		if (P > 5)
			P = 5;

		mclk_Hz = ((ExtClk_Hz / 2) * N) / (M * (1 << P));
		dprintk("stv0367cab_get_mclk BYPASS_PLLXN mclk_Hz=%d\n",
								mclk_Hz);
	} else
		mclk_Hz = ExtClk_Hz;

	dprintk("stv0367cab_get_mclk final mclk_Hz=%d\n", mclk_Hz);

	return mclk_Hz;
}