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
struct dvb_frontend {struct drx39xxj_state* demodulator_priv; } ;
struct drx_demod_instance {int dummy; } ;
struct drx39xxj_state {struct drx_demod_instance* demod; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
typedef  enum drx_lock_status { ____Placeholder_drx_lock_status } drx_lock_status ;

/* Variables and functions */
#define  DRX_LOCKED 139 
#define  DRX_LOCK_STATE_1 138 
#define  DRX_LOCK_STATE_2 137 
#define  DRX_LOCK_STATE_3 136 
#define  DRX_LOCK_STATE_4 135 
#define  DRX_LOCK_STATE_5 134 
#define  DRX_LOCK_STATE_6 133 
#define  DRX_LOCK_STATE_7 132 
#define  DRX_LOCK_STATE_8 131 
#define  DRX_LOCK_STATE_9 130 
#define  DRX_NEVER_LOCK 129 
#define  DRX_NOT_LOCKED 128 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int ctrl_lock_status (struct drx_demod_instance*,int*) ; 
 int /*<<< orphan*/  ctrl_sig_quality (struct drx_demod_instance*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int drx39xxj_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct drx39xxj_state *state = fe->demodulator_priv;
	struct drx_demod_instance *demod = state->demod;
	int result;
	enum drx_lock_status lock_status;

	*status = 0;

	result = ctrl_lock_status(demod, &lock_status);
	if (result != 0) {
		pr_err("drx39xxj: could not get lock status!\n");
		*status = 0;
	}

	switch (lock_status) {
	case DRX_NEVER_LOCK:
		*status = 0;
		pr_err("drx says NEVER_LOCK\n");
		break;
	case DRX_NOT_LOCKED:
		*status = 0;
		break;
	case DRX_LOCK_STATE_1:
	case DRX_LOCK_STATE_2:
	case DRX_LOCK_STATE_3:
	case DRX_LOCK_STATE_4:
	case DRX_LOCK_STATE_5:
	case DRX_LOCK_STATE_6:
	case DRX_LOCK_STATE_7:
	case DRX_LOCK_STATE_8:
	case DRX_LOCK_STATE_9:
		*status = FE_HAS_SIGNAL
		    | FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC;
		break;
	case DRX_LOCKED:
		*status = FE_HAS_SIGNAL
		    | FE_HAS_CARRIER
		    | FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
		break;
	default:
		pr_err("Lock state unknown %d\n", lock_status);
	}
	ctrl_sig_quality(demod, lock_status);

	return 0;
}