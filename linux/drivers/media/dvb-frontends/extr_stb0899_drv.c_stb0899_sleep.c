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
struct stb0899_state {int /*<<< orphan*/  verbose; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  STB0899_POSTPROC_GPIO_POWER ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stb0899_postproc (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb0899_sleep(struct dvb_frontend *fe)
{
	struct stb0899_state *state = fe->demodulator_priv;
/*
	u8 reg;
*/
	dprintk(state->verbose, FE_DEBUG, 1, "Going to Sleep .. (Really tired .. :-))");
	/* post process event */
	stb0899_postproc(state, STB0899_POSTPROC_GPIO_POWER, 0);

	return 0;
}