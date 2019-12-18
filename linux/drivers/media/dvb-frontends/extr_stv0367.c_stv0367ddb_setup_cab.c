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
struct stv0367_state {int /*<<< orphan*/  activedemod; TYPE_2__* config; int /*<<< orphan*/  fe; TYPE_1__* cab_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  xtal; } ;
struct TYPE_3__ {int /*<<< orphan*/  adc_clk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  R367TER_ANACTRL ; 
 int /*<<< orphan*/  R367TER_ANADIGCTRL ; 
 int /*<<< orphan*/  R367TER_DEBUG_LT4 ; 
 int /*<<< orphan*/  R367TER_DEBUG_LT5 ; 
 int /*<<< orphan*/  R367TER_DEBUG_LT6 ; 
 int /*<<< orphan*/  R367TER_DEBUG_LT7 ; 
 int /*<<< orphan*/  R367TER_DEBUG_LT8 ; 
 int /*<<< orphan*/  R367TER_DEBUG_LT9 ; 
 int /*<<< orphan*/  R367TER_DUAL_AD12 ; 
 int /*<<< orphan*/  R367TER_TOPCTRL ; 
 int /*<<< orphan*/  STV0367_ICSPEED_58000 ; 
 int /*<<< orphan*/  demod_cab ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stv0367_pll_setup (struct stv0367_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0367_writereg (struct stv0367_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv0367cab_get_adc_freq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0367cab_get_mclk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stv0367ddb_setup_cab(struct stv0367_state *state)
{
	stv0367_writereg(state, R367TER_DEBUG_LT4, 0x00);
	stv0367_writereg(state, R367TER_DEBUG_LT5, 0x01);
	stv0367_writereg(state, R367TER_DEBUG_LT6, 0x06); /* R367CAB_CTRL_1 */
	stv0367_writereg(state, R367TER_DEBUG_LT7, 0x03); /* R367CAB_CTRL_2 */
	stv0367_writereg(state, R367TER_DEBUG_LT8, 0x00);
	stv0367_writereg(state, R367TER_DEBUG_LT9, 0x00);

	/* Tuner Setup */
	/* Buffer Q disabled, I Enabled, signed ADC */
	stv0367_writereg(state, R367TER_ANADIGCTRL, 0x8B);
	/* ADCQ disabled */
	stv0367_writereg(state, R367TER_DUAL_AD12, 0x04);

	/* Clock setup */
	/* PLL bypassed and disabled */
	stv0367_writereg(state, R367TER_ANACTRL, 0x0D);
	/* Set QAM */
	stv0367_writereg(state, R367TER_TOPCTRL, 0x10);

	/* IC runs at 58 MHz with a 27 MHz crystal */
	stv0367_pll_setup(state, STV0367_ICSPEED_58000, state->config->xtal);

	msleep(50);
	/* PLL enabled and used */
	stv0367_writereg(state, R367TER_ANACTRL, 0x00);

	state->cab_state->mclk = stv0367cab_get_mclk(&state->fe,
		state->config->xtal);
	state->cab_state->adc_clk = stv0367cab_get_adc_freq(&state->fe,
		state->config->xtal);

	state->activedemod = demod_cab;
}