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
struct dvb_frontend {struct as102_state* demodulator_priv; } ;
struct as10x_tune_status {int tune_state; int /*<<< orphan*/  BER; int /*<<< orphan*/  PER; int /*<<< orphan*/  signal_strength; int /*<<< orphan*/  member_0; } ;
struct as102_state {int /*<<< orphan*/  demod_stats; int /*<<< orphan*/  priv; TYPE_1__* ops; int /*<<< orphan*/  ber; int /*<<< orphan*/  signal_strength; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_2__ {int (* get_status ) (int /*<<< orphan*/ ,struct as10x_tune_status*) ;int (* get_stats ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int TUNE_STATUS_NOT_TUNED ; 
#define  TUNE_STATUS_SIGNAL_DVB_OK 130 
#define  TUNE_STATUS_STREAM_DETECTED 129 
#define  TUNE_STATUS_STREAM_TUNED 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct as10x_tune_status*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int as102_fe_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	int ret = 0;
	struct as102_state *state = fe->demodulator_priv;
	struct as10x_tune_status tstate = { 0 };

	/* send abilis command: GET_TUNE_STATUS */
	ret = state->ops->get_status(state->priv, &tstate);
	if (ret < 0)
		return ret;

	state->signal_strength  = tstate.signal_strength;
	state->ber  = tstate.BER;

	switch (tstate.tune_state) {
	case TUNE_STATUS_SIGNAL_DVB_OK:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		break;
	case TUNE_STATUS_STREAM_DETECTED:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_SYNC |
			  FE_HAS_VITERBI;
		break;
	case TUNE_STATUS_STREAM_TUNED:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_SYNC |
			  FE_HAS_LOCK | FE_HAS_VITERBI;
		break;
	default:
		*status = TUNE_STATUS_NOT_TUNED;
	}

	pr_debug("as102: tuner status: 0x%02x, strength %d, per: %d, ber: %d\n",
		 tstate.tune_state, tstate.signal_strength,
		 tstate.PER, tstate.BER);

	if (!(*status & FE_HAS_LOCK)) {
		memset(&state->demod_stats, 0, sizeof(state->demod_stats));
		return 0;
	}

	ret = state->ops->get_stats(state->priv, &state->demod_stats);
	if (ret < 0)
		memset(&state->demod_stats, 0, sizeof(state->demod_stats));

	return ret;
}