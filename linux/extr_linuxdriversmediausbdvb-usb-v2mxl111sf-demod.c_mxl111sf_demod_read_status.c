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
struct mxl111sf_demod_state {int dummy; } ;
struct dvb_frontend {struct mxl111sf_demod_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int mxl1x1sf_demod_get_fec_lock_status (struct mxl111sf_demod_state*,int*) ; 
 int mxl1x1sf_demod_get_rs_lock_status (struct mxl111sf_demod_state*,int*) ; 
 int mxl1x1sf_demod_get_sync_lock_status (struct mxl111sf_demod_state*,int*) ; 
 int mxl1x1sf_demod_get_tps_lock_status (struct mxl111sf_demod_state*,int*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static int mxl111sf_demod_read_status(struct dvb_frontend *fe,
				      enum fe_status *status)
{
	struct mxl111sf_demod_state *state = fe->demodulator_priv;
	int ret, locked, cr_lock, sync_lock, fec_lock;

	*status = 0;

	ret = mxl1x1sf_demod_get_rs_lock_status(state, &locked);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl1x1sf_demod_get_tps_lock_status(state, &cr_lock);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl1x1sf_demod_get_sync_lock_status(state, &sync_lock);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl1x1sf_demod_get_fec_lock_status(state, &fec_lock);
	if (mxl_fail(ret))
		goto fail;

	if (locked)
		*status |= FE_HAS_SIGNAL;
	if (cr_lock)
		*status |= FE_HAS_CARRIER;
	if (sync_lock)
		*status |= FE_HAS_SYNC;
	if (fec_lock) /* false positives? */
		*status |= FE_HAS_VITERBI;

	if ((locked) && (cr_lock) && (sync_lock))
		*status |= FE_HAS_LOCK;
fail:
	return ret;
}