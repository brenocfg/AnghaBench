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
struct stb0899_state {int dummy; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  STB0899_POSTPROC_GPIO_POWER ; 
 int STB0899_SELOSCI ; 
 int /*<<< orphan*/  STB0899_STOPCLK1 ; 
 int /*<<< orphan*/  STB0899_STOPCLK2 ; 
 int /*<<< orphan*/  STB0899_SYNTCTRL ; 
 int /*<<< orphan*/  stb0899_postproc (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 
 int stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stb0899_wakeup(struct dvb_frontend *fe)
{
	int rc;
	struct stb0899_state *state = fe->demodulator_priv;

	if ((rc = stb0899_write_reg(state, STB0899_SYNTCTRL, STB0899_SELOSCI)))
		return rc;
	/* Activate all clocks; DVB-S2 registers are inaccessible otherwise. */
	if ((rc = stb0899_write_reg(state, STB0899_STOPCLK1, 0x00)))
		return rc;
	if ((rc = stb0899_write_reg(state, STB0899_STOPCLK2, 0x00)))
		return rc;

	/* post process event */
	stb0899_postproc(state, STB0899_POSTPROC_GPIO_POWER, 1);

	return 0;
}