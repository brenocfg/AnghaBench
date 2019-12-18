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
typedef  scalar_t__ u8 ;
struct dvb_frontend {struct dst_state* demodulator_priv; } ;
struct dst_state {scalar_t__ type_flags; scalar_t__ dst_type; int diseq_flags; int /*<<< orphan*/  dst_mutex; void** tx_tuna; scalar_t__ decode_snr; scalar_t__ decode_strength; scalar_t__ decode_lock; scalar_t__ decode_freq; } ;

/* Variables and functions */
 scalar_t__ ACK ; 
 int ATTEMPT_TUNE ; 
 int DST_TYPE_HAS_VLF ; 
 scalar_t__ DST_TYPE_IS_ATSC ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 int EIO ; 
 int FIXED_COMM ; 
 int /*<<< orphan*/  GET_ACK ; 
 int HAS_LOCK ; 
 int HAS_POWER ; 
 int /*<<< orphan*/  SEC_VOLTAGE_13 ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 void* dst_check_sum (void**,int) ; 
 scalar_t__ dst_comm_init (struct dst_state*) ; 
 int dst_get_tuna (struct dst_state*) ; 
 scalar_t__ dst_pio_disable (struct dst_state*) ; 
 int /*<<< orphan*/  dst_set_voltage (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ read_dst (struct dst_state*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int write_dst (struct dst_state*,void**,int) ; 

__attribute__((used)) static int dst_write_tuna(struct dvb_frontend *fe)
{
	struct dst_state *state = fe->demodulator_priv;
	int retval;
	u8 reply;

	dprintk(2, "type_flags 0x%x\n", state->type_flags);
	state->decode_freq = 0;
	state->decode_lock = state->decode_strength = state->decode_snr = 0;
	if (state->dst_type == DST_TYPE_IS_SAT) {
		if (!(state->diseq_flags & HAS_POWER))
			dst_set_voltage(fe, SEC_VOLTAGE_13);
	}
	state->diseq_flags &= ~(HAS_LOCK | ATTEMPT_TUNE);
	mutex_lock(&state->dst_mutex);
	if ((dst_comm_init(state)) < 0) {
		dprintk(3, "DST Communication initialization failed.\n");
		goto error;
	}
//	if (state->type_flags & DST_TYPE_HAS_NEWTUNE) {
	if ((state->type_flags & DST_TYPE_HAS_VLF) &&
		(!(state->dst_type == DST_TYPE_IS_ATSC))) {

		state->tx_tuna[9] = dst_check_sum(&state->tx_tuna[0], 9);
		retval = write_dst(state, &state->tx_tuna[0], 10);
	} else {
		state->tx_tuna[9] = dst_check_sum(&state->tx_tuna[2], 7);
		retval = write_dst(state, &state->tx_tuna[2], FIXED_COMM);
	}
	if (retval < 0) {
		dst_pio_disable(state);
		dprintk(3, "write not successful\n");
		goto werr;
	}
	if ((dst_pio_disable(state)) < 0) {
		dprintk(3, "DST PIO disable failed !\n");
		goto error;
	}
	if ((read_dst(state, &reply, GET_ACK) < 0)) {
		dprintk(3, "read verify not successful.\n");
		goto error;
	}
	if (reply != ACK) {
		dprintk(3, "write not acknowledged 0x%02x\n", reply);
		goto error;
	}
	state->diseq_flags |= ATTEMPT_TUNE;
	retval = dst_get_tuna(state);
werr:
	mutex_unlock(&state->dst_mutex);
	return retval;

error:
	mutex_unlock(&state->dst_mutex);
	return -EIO;
}