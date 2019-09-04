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
struct dvb_frontend {struct dst_state* demodulator_priv; } ;
struct dst_state {int diseq_flags; scalar_t__ decode_lock; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int HAS_LOCK ; 

__attribute__((used)) static int dst_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct dst_state *state = fe->demodulator_priv;

	*status = 0;
	if (state->diseq_flags & HAS_LOCK) {
//		dst_get_signal(state);	// don't require(?) to ask MCU
		if (state->decode_lock)
			*status |= FE_HAS_LOCK | FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_SYNC | FE_HAS_VITERBI;
	}

	return 0;
}