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
typedef  int u16 ;
struct dvb_frontend {struct cx24110_state* demodulator_priv; } ;
struct cx24110_state {int lastesn0; } ;

/* Variables and functions */
 int cx24110_readreg (struct cx24110_state*,int) ; 
 int /*<<< orphan*/  cx24110_writereg (struct cx24110_state*,int,int) ; 

__attribute__((used)) static int cx24110_read_snr(struct dvb_frontend* fe, u16* snr)
{
	struct cx24110_state *state = fe->demodulator_priv;

	/* no provision in hardware. Can be computed from the Es/N0 estimator, but I don't know how. */
	if(cx24110_readreg(state,0x6a)&0x80) {
		/* the Es/N0 error counter has finished one counting window */
		state->lastesn0=cx24110_readreg(state,0x69)|
			(cx24110_readreg(state,0x68)<<8);
		cx24110_writereg(state,0x6a,0x84); /* start new count window */
	}
	*snr = state->lastesn0;

	return 0;
}