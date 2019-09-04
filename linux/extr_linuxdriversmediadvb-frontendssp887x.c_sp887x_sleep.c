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
struct sp887x_state {int dummy; } ;
struct dvb_frontend {struct sp887x_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  sp887x_writereg (struct sp887x_state*,int,int) ; 

__attribute__((used)) static int sp887x_sleep(struct dvb_frontend* fe)
{
	struct sp887x_state* state = fe->demodulator_priv;

	/* tristate TS output and disable interface pins */
	sp887x_writereg(state, 0xc18, 0x000);

	return 0;
}