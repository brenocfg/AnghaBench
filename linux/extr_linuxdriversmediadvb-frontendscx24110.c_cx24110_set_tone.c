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
struct dvb_frontend {struct cx24110_state* demodulator_priv; } ;
struct cx24110_state {int dummy; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;

/* Variables and functions */
 int SEC_TONE_ON ; 
 int cx24110_readreg (struct cx24110_state*,int) ; 
 int cx24110_writereg (struct cx24110_state*,int,int) ; 

__attribute__((used)) static int cx24110_set_tone(struct dvb_frontend *fe,
			    enum fe_sec_tone_mode tone)
{
	struct cx24110_state *state = fe->demodulator_priv;

	return cx24110_writereg(state,0x76,(cx24110_readreg(state,0x76)&~0x10)|(((tone==SEC_TONE_ON))?0x10:0));
}