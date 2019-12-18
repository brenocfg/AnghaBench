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
typedef  int u32 ;
struct dvb_frontend {struct drxd_state* demodulator_priv; } ;
struct drxd_state {int dummy; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRXD_status (struct drxd_state*,int*) ; 
 int DRX_LOCK_DEMOD ; 
 int DRX_LOCK_FEC ; 
 int DRX_LOCK_MPEG ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 

__attribute__((used)) static int drxd_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct drxd_state *state = fe->demodulator_priv;
	u32 lock;

	DRXD_status(state, &lock);
	*status = 0;
	/* No MPEG lock in V255 firmware, bug ? */
#if 1
	if (lock & DRX_LOCK_MPEG)
		*status |= FE_HAS_LOCK;
#else
	if (lock & DRX_LOCK_FEC)
		*status |= FE_HAS_LOCK;
#endif
	if (lock & DRX_LOCK_FEC)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC;
	if (lock & DRX_LOCK_DEMOD)
		*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;

	return 0;
}