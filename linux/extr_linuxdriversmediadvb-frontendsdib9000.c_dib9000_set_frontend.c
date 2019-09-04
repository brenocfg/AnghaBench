#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend_parametersContext {void* status; } ;
struct TYPE_22__ {void* delivery_system; } ;
struct dvb_frontend {TYPE_6__ dtv_property_cache; struct dib9000_state* demodulator_priv; } ;
struct dtv_frontend_properties {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  output_mode; } ;
struct TYPE_18__ {TYPE_1__ cfg; } ;
struct TYPE_19__ {TYPE_2__ d9; } ;
struct dib9000_state {int pid_ctrl_index; int get_frontend_internal; TYPE_4__* pid_ctrl; TYPE_7__** fe; int /*<<< orphan*/  demod_lock; TYPE_3__ chip; struct dvb_frontend_parametersContext channel_status; } ;
struct TYPE_21__ {scalar_t__ frequency; scalar_t__ bandwidth_hz; scalar_t__ transmission_mode; scalar_t__ guard_interval; scalar_t__ modulation; scalar_t__ code_rate_HP; void* delivery_system; } ;
struct TYPE_23__ {TYPE_5__ dtv_property_cache; } ;
struct TYPE_20__ {scalar_t__ cmd; int /*<<< orphan*/  onoff; int /*<<< orphan*/  pid; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 void* CHANNEL_STATUS_PARAMETERS_SET ; 
 void* CHANNEL_STATUS_PARAMETERS_UNKNOWN ; 
 int /*<<< orphan*/  CT_DEMOD_START ; 
 scalar_t__ DIB9000_PID_FILTER ; 
 scalar_t__ DIB9000_PID_FILTER_CTRL ; 
 scalar_t__ FEC_AUTO ; 
 int FE_CALLBACK_TIME_NEVER ; 
 int /*<<< orphan*/  FE_STATUS_TUNE_PENDING ; 
 scalar_t__ GUARD_INTERVAL_AUTO ; 
 size_t MAX_NUMBER_OF_FRONTENDS ; 
 int /*<<< orphan*/  OUTMODE_DIVERSITY ; 
 int /*<<< orphan*/  OUTMODE_HIGH_Z ; 
 scalar_t__ QAM_AUTO ; 
 void* SYS_DVBT ; 
 scalar_t__ TRANSMISSION_MODE_AUTO ; 
 int /*<<< orphan*/  dib9000_fw_pid_filter (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib9000_fw_pid_filter_ctrl (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib9000_fw_set_diversity_in (TYPE_7__*,int) ; 
 int /*<<< orphan*/  dib9000_fw_set_output_mode (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int dib9000_fw_tune (TYPE_7__*) ; 
 int /*<<< orphan*/  dib9000_get_frontend (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dib9000_get_status (TYPE_7__*) ; 
 int /*<<< orphan*/  dib9000_set_channel_status (TYPE_7__*,struct dvb_frontend_parametersContext*) ; 
 int /*<<< orphan*/  dib9000_set_tune_state (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib9000_set_frontend(struct dvb_frontend *fe)
{
	struct dib9000_state *state = fe->demodulator_priv;
	int sleep_time, sleep_time_slave;
	u32 frontend_status;
	u8 nbr_pending, exit_condition, index_frontend, index_frontend_success;
	struct dvb_frontend_parametersContext channel_status;

	/* check that the correct parameters are set */
	if (state->fe[0]->dtv_property_cache.frequency == 0) {
		dprintk("dib9000: must specify frequency\n");
		return 0;
	}

	if (state->fe[0]->dtv_property_cache.bandwidth_hz == 0) {
		dprintk("dib9000: must specify bandwidth\n");
		return 0;
	}

	state->pid_ctrl_index = -1; /* postpone the pid filtering cmd */
	if (mutex_lock_interruptible(&state->demod_lock) < 0) {
		dprintk("could not get the lock\n");
		return 0;
	}

	fe->dtv_property_cache.delivery_system = SYS_DVBT;

	/* set the master status */
	if (state->fe[0]->dtv_property_cache.transmission_mode == TRANSMISSION_MODE_AUTO ||
	    state->fe[0]->dtv_property_cache.guard_interval == GUARD_INTERVAL_AUTO ||
	    state->fe[0]->dtv_property_cache.modulation == QAM_AUTO ||
	    state->fe[0]->dtv_property_cache.code_rate_HP == FEC_AUTO) {
		/* no channel specified, autosearch the channel */
		state->channel_status.status = CHANNEL_STATUS_PARAMETERS_UNKNOWN;
	} else
		state->channel_status.status = CHANNEL_STATUS_PARAMETERS_SET;

	/* set mode and status for the different frontends */
	for (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
		dib9000_fw_set_diversity_in(state->fe[index_frontend], 1);

		/* synchronization of the cache */
		memcpy(&state->fe[index_frontend]->dtv_property_cache, &fe->dtv_property_cache, sizeof(struct dtv_frontend_properties));

		state->fe[index_frontend]->dtv_property_cache.delivery_system = SYS_DVBT;
		dib9000_fw_set_output_mode(state->fe[index_frontend], OUTMODE_HIGH_Z);

		dib9000_set_channel_status(state->fe[index_frontend], &state->channel_status);
		dib9000_set_tune_state(state->fe[index_frontend], CT_DEMOD_START);
	}

	/* actual tune */
	exit_condition = 0;	/* 0: tune pending; 1: tune failed; 2:tune success */
	index_frontend_success = 0;
	do {
		sleep_time = dib9000_fw_tune(state->fe[0]);
		for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
			sleep_time_slave = dib9000_fw_tune(state->fe[index_frontend]);
			if (sleep_time == FE_CALLBACK_TIME_NEVER)
				sleep_time = sleep_time_slave;
			else if ((sleep_time_slave != FE_CALLBACK_TIME_NEVER) && (sleep_time_slave > sleep_time))
				sleep_time = sleep_time_slave;
		}
		if (sleep_time != FE_CALLBACK_TIME_NEVER)
			msleep(sleep_time / 10);
		else
			break;

		nbr_pending = 0;
		exit_condition = 0;
		index_frontend_success = 0;
		for (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
			frontend_status = -dib9000_get_status(state->fe[index_frontend]);
			if (frontend_status > -FE_STATUS_TUNE_PENDING) {
				exit_condition = 2;	/* tune success */
				index_frontend_success = index_frontend;
				break;
			}
			if (frontend_status == -FE_STATUS_TUNE_PENDING)
				nbr_pending++;	/* some frontends are still tuning */
		}
		if ((exit_condition != 2) && (nbr_pending == 0))
			exit_condition = 1;	/* if all tune are done and no success, exit: tune failed */

	} while (exit_condition == 0);

	/* check the tune result */
	if (exit_condition == 1) {	/* tune failed */
		dprintk("tune failed\n");
		mutex_unlock(&state->demod_lock);
		/* tune failed; put all the pid filtering cmd to junk */
		state->pid_ctrl_index = -1;
		return 0;
	}

	dprintk("tune success on frontend%i\n", index_frontend_success);

	/* synchronize all the channel cache */
	state->get_frontend_internal = 1;
	dib9000_get_frontend(state->fe[0], &state->fe[0]->dtv_property_cache);
	state->get_frontend_internal = 0;

	/* retune the other frontends with the found channel */
	channel_status.status = CHANNEL_STATUS_PARAMETERS_SET;
	for (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
		/* only retune the frontends which was not tuned success */
		if (index_frontend != index_frontend_success) {
			dib9000_set_channel_status(state->fe[index_frontend], &channel_status);
			dib9000_set_tune_state(state->fe[index_frontend], CT_DEMOD_START);
		}
	}
	do {
		sleep_time = FE_CALLBACK_TIME_NEVER;
		for (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
			if (index_frontend != index_frontend_success) {
				sleep_time_slave = dib9000_fw_tune(state->fe[index_frontend]);
				if (sleep_time == FE_CALLBACK_TIME_NEVER)
					sleep_time = sleep_time_slave;
				else if ((sleep_time_slave != FE_CALLBACK_TIME_NEVER) && (sleep_time_slave > sleep_time))
					sleep_time = sleep_time_slave;
			}
		}
		if (sleep_time != FE_CALLBACK_TIME_NEVER)
			msleep(sleep_time / 10);
		else
			break;

		nbr_pending = 0;
		for (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
			if (index_frontend != index_frontend_success) {
				frontend_status = -dib9000_get_status(state->fe[index_frontend]);
				if ((index_frontend != index_frontend_success) && (frontend_status == -FE_STATUS_TUNE_PENDING))
					nbr_pending++;	/* some frontends are still tuning */
			}
		}
	} while (nbr_pending != 0);

	/* set the output mode */
	dib9000_fw_set_output_mode(state->fe[0], state->chip.d9.cfg.output_mode);
	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++)
		dib9000_fw_set_output_mode(state->fe[index_frontend], OUTMODE_DIVERSITY);

	/* turn off the diversity for the last frontend */
	dib9000_fw_set_diversity_in(state->fe[index_frontend - 1], 0);

	mutex_unlock(&state->demod_lock);
	if (state->pid_ctrl_index >= 0) {
		u8 index_pid_filter_cmd;
		u8 pid_ctrl_index = state->pid_ctrl_index;

		state->pid_ctrl_index = -2;
		for (index_pid_filter_cmd = 0;
				index_pid_filter_cmd <= pid_ctrl_index;
				index_pid_filter_cmd++) {
			if (state->pid_ctrl[index_pid_filter_cmd].cmd == DIB9000_PID_FILTER_CTRL)
				dib9000_fw_pid_filter_ctrl(state->fe[0],
						state->pid_ctrl[index_pid_filter_cmd].onoff);
			else if (state->pid_ctrl[index_pid_filter_cmd].cmd == DIB9000_PID_FILTER)
				dib9000_fw_pid_filter(state->fe[0],
						state->pid_ctrl[index_pid_filter_cmd].id,
						state->pid_ctrl[index_pid_filter_cmd].pid,
						state->pid_ctrl[index_pid_filter_cmd].onoff);
		}
	}
	/* do not postpone any more the pid filtering */
	state->pid_ctrl_index = -2;

	return 0;
}