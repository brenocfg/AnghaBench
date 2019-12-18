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
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int cx24110_readreg (struct cx24110_state*,int) ; 

__attribute__((used)) static int cx24110_read_status(struct dvb_frontend *fe,
			       enum fe_status *status)
{
	struct cx24110_state *state = fe->demodulator_priv;

	int sync = cx24110_readreg (state, 0x55);

	*status = 0;

	if (sync & 0x10)
		*status |= FE_HAS_SIGNAL;

	if (sync & 0x08)
		*status |= FE_HAS_CARRIER;

	sync = cx24110_readreg (state, 0x08);

	if (sync & 0x40)
		*status |= FE_HAS_VITERBI;

	if (sync & 0x20)
		*status |= FE_HAS_SYNC;

	if ((sync & 0x60) == 0x60)
		*status |= FE_HAS_LOCK;

	return 0;
}