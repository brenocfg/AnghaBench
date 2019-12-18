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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct TYPE_2__ {scalar_t__ status; } ;
struct dib9000_state {int tune_state; int /*<<< orphan*/  status; int /*<<< orphan*/ * i2c_read_buffer; TYPE_1__ channel_status; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 scalar_t__ CHANNEL_STATUS_PARAMETERS_UNKNOWN ; 
#define  CT_DEMOD_START 129 
#define  CT_DEMOD_STEP_1 128 
 void* CT_DEMOD_STOP ; 
 int FE_CALLBACK_TIME_NEVER ; 
 int /*<<< orphan*/  FE_MM_R_CHANNEL_SEARCH_STATE ; 
 int /*<<< orphan*/  FE_MM_R_CHANNEL_TUNE_STATE ; 
 int /*<<< orphan*/  FE_MM_W_CHANNEL_CONTEXT ; 
 int /*<<< orphan*/  FE_MM_W_FE_INFO ; 
 int /*<<< orphan*/  FE_STATUS_DEMOD_SUCCESS ; 
 int /*<<< orphan*/  FE_STATUS_LOCKED ; 
 int /*<<< orphan*/  FE_STATUS_TUNE_FAILED ; 
 int /*<<< orphan*/  OUT_MSG_FE_CHANNEL_SEARCH ; 
 int /*<<< orphan*/  OUT_MSG_FE_CHANNEL_TUNE ; 
 int /*<<< orphan*/  dib9000_fw_set_channel_head (struct dib9000_state*) ; 
 int /*<<< orphan*/  dib9000_fw_set_channel_union (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib9000_mbx_send (struct dib9000_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib9000_risc_mem_read (struct dib9000_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dib9000_risc_mem_write (struct dib9000_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fe_info ; 

__attribute__((used)) static int dib9000_fw_tune(struct dvb_frontend *fe)
{
	struct dib9000_state *state = fe->demodulator_priv;
	int ret = 10, search = state->channel_status.status == CHANNEL_STATUS_PARAMETERS_UNKNOWN;
	s8 i;

	switch (state->tune_state) {
	case CT_DEMOD_START:
		dib9000_fw_set_channel_head(state);

		/* write the channel context - a channel is initialized to 0, so it is OK */
		dib9000_risc_mem_write(state, FE_MM_W_CHANNEL_CONTEXT, (u8 *) fe_info);
		dib9000_risc_mem_write(state, FE_MM_W_FE_INFO, (u8 *) fe_info);

		if (search)
			dib9000_mbx_send(state, OUT_MSG_FE_CHANNEL_SEARCH, NULL, 0);
		else {
			dib9000_fw_set_channel_union(fe);
			dib9000_mbx_send(state, OUT_MSG_FE_CHANNEL_TUNE, NULL, 0);
		}
		state->tune_state = CT_DEMOD_STEP_1;
		break;
	case CT_DEMOD_STEP_1:
		if (search)
			dib9000_risc_mem_read(state, FE_MM_R_CHANNEL_SEARCH_STATE, state->i2c_read_buffer, 1);
		else
			dib9000_risc_mem_read(state, FE_MM_R_CHANNEL_TUNE_STATE, state->i2c_read_buffer, 1);
		i = (s8)state->i2c_read_buffer[0];
		switch (i) {	/* something happened */
		case 0:
			break;
		case -2:	/* tps locks are "slower" than MPEG locks -> even in autosearch data is OK here */
			if (search)
				state->status = FE_STATUS_DEMOD_SUCCESS;
			else {
				state->tune_state = CT_DEMOD_STOP;
				state->status = FE_STATUS_LOCKED;
			}
			break;
		default:
			state->status = FE_STATUS_TUNE_FAILED;
			state->tune_state = CT_DEMOD_STOP;
			break;
		}
		break;
	default:
		ret = FE_CALLBACK_TIME_NEVER;
		break;
	}

	return ret;
}