#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {struct cinergyt2_fe_state* demodulator_priv; } ;
struct TYPE_2__ {int lock_bits; int /*<<< orphan*/  gain; } ;
struct cinergyt2_fe_state {TYPE_1__ status; int /*<<< orphan*/  data_mutex; int /*<<< orphan*/ * data; int /*<<< orphan*/  d; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int /*<<< orphan*/  CINERGYT2_EP1_GET_TUNER_STATUS ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int dvb_usb_generic_rw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cinergyt2_fe_read_status(struct dvb_frontend *fe,
				    enum fe_status *status)
{
	struct cinergyt2_fe_state *state = fe->demodulator_priv;
	int ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = CINERGYT2_EP1_GET_TUNER_STATUS;

	ret = dvb_usb_generic_rw(state->d, state->data, 1,
				 state->data, sizeof(state->status), 0);
	if (!ret)
		memcpy(&state->status, state->data, sizeof(state->status));
	mutex_unlock(&state->data_mutex);

	if (ret < 0)
		return ret;

	*status = 0;

	if (0xffff - le16_to_cpu(state->status.gain) > 30)
		*status |= FE_HAS_SIGNAL;
	if (state->status.lock_bits & (1 << 6))
		*status |= FE_HAS_LOCK;
	if (state->status.lock_bits & (1 << 5))
		*status |= FE_HAS_SYNC;
	if (state->status.lock_bits & (1 << 4))
		*status |= FE_HAS_CARRIER;
	if (state->status.lock_bits & (1 << 1))
		*status |= FE_HAS_VITERBI;

	if ((*status & (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC)) !=
			(FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_LOCK;

	return 0;
}