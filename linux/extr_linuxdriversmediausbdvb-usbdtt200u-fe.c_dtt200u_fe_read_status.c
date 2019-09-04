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
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; } ;
struct dtt200u_fe_state {int* data; int /*<<< orphan*/  data_mutex; int /*<<< orphan*/  d; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int FE_TIMEDOUT ; 
 int GET_TUNE_STATUS ; 
 int dvb_usb_generic_rw (int /*<<< orphan*/ ,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dtt200u_fe_read_status(struct dvb_frontend *fe,
				  enum fe_status *stat)
{
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	int ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = GET_TUNE_STATUS;

	ret = dvb_usb_generic_rw(state->d, state->data, 1, state->data, 3, 0);
	if (ret < 0) {
		*stat = 0;
		mutex_unlock(&state->data_mutex);
		return ret;
	}

	switch (state->data[0]) {
		case 0x01:
			*stat = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
			break;
		case 0x00: /* pending */
			*stat = FE_TIMEDOUT; /* during set_frontend */
			break;
		default:
		case 0x02: /* failed */
			*stat = 0;
			break;
	}
	mutex_unlock(&state->data_mutex);
	return 0;
}