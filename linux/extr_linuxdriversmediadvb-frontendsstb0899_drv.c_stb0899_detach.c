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
 int /*<<< orphan*/  stb0899_postproc (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stb0899_detach(struct dvb_frontend *fe)
{
	struct stb0899_state *state = fe->demodulator_priv;

	/* post process event */
	stb0899_postproc(state, STB0899_POSTPROC_GPIO_POWER, 0);
}