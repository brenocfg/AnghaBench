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
struct stv0367_state {int /*<<< orphan*/  activedemod; TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  xtal; } ;

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
 int /*<<< orphan*/  STV0367_ICSPEED_53125 ; 
 int /*<<< orphan*/  demod_ter ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stv0367_pll_setup (struct stv0367_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0367_writereg (struct stv0367_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stv0367ddb_setup_ter(struct stv0367_state *state)
{
	stv0367_writereg(state, R367TER_DEBUG_LT4, 0x00);
	stv0367_writereg(state, R367TER_DEBUG_LT5, 0x00);
	stv0367_writereg(state, R367TER_DEBUG_LT6, 0x00); /* R367CAB_CTRL_1 */
	stv0367_writereg(state, R367TER_DEBUG_LT7, 0x00); /* R367CAB_CTRL_2 */
	stv0367_writereg(state, R367TER_DEBUG_LT8, 0x00);
	stv0367_writereg(state, R367TER_DEBUG_LT9, 0x00);

	/* Tuner Setup */
	/* Buffer Q disabled, I Enabled, unsigned ADC */
	stv0367_writereg(state, R367TER_ANADIGCTRL, 0x89);
	stv0367_writereg(state, R367TER_DUAL_AD12, 0x04); /* ADCQ disabled */

	/* Clock setup */
	/* PLL bypassed and disabled */
	stv0367_writereg(state, R367TER_ANACTRL, 0x0D);
	stv0367_writereg(state, R367TER_TOPCTRL, 0x00); /* Set OFDM */

	/* IC runs at 54 MHz with a 27 MHz crystal */
	stv0367_pll_setup(state, STV0367_ICSPEED_53125, state->config->xtal);

	msleep(50);
	/* PLL enabled and used */
	stv0367_writereg(state, R367TER_ANACTRL, 0x00);

	state->activedemod = demod_ter;
}