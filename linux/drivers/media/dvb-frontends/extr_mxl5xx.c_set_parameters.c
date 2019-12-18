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
typedef  int u8 ;
typedef  int u32 ;
struct mxl {TYPE_1__* base; int /*<<< orphan*/  tuner; int /*<<< orphan*/  tuner_in_use; int /*<<< orphan*/  demod; } ;
struct dtv_frontend_properties {int frequency; int symbol_rate; int delivery_system; int /*<<< orphan*/  scrambling_sequence_index; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct mxl* demodulator_priv; } ;
struct MXL_HYDRA_DEMOD_PARAM_T {int frequency_in_hz; int symbol_rate_in_hz; int max_carrier_offset_in_mhz; int /*<<< orphan*/  fec_code_rate; int /*<<< orphan*/  spectrum_inversion; int /*<<< orphan*/  demod_index; int /*<<< orphan*/  tuner_index; int /*<<< orphan*/  pilots; int /*<<< orphan*/  modulation_scheme; void* roll_off; int /*<<< orphan*/  standard; } ;
typedef  int /*<<< orphan*/  demod_chan_cfg ;
struct TYPE_2__ {int /*<<< orphan*/  tune_lock; scalar_t__ next_tune; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_HYDRA_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct MXL_HYDRA_DEMOD_PARAM_T*,int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MXL_CMD_WRITE ; 
 int MXL_HYDRA_CMD_HEADER_SIZE ; 
 int /*<<< orphan*/  MXL_HYDRA_DEMOD_SET_PARAM_CMD ; 
 int /*<<< orphan*/  MXL_HYDRA_DSS ; 
 int /*<<< orphan*/  MXL_HYDRA_DVBS ; 
 int /*<<< orphan*/  MXL_HYDRA_DVBS2 ; 
 int /*<<< orphan*/  MXL_HYDRA_FEC_AUTO ; 
 int /*<<< orphan*/  MXL_HYDRA_MOD_AUTO ; 
 int /*<<< orphan*/  MXL_HYDRA_MOD_QPSK ; 
 int MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN ; 
 int /*<<< orphan*/  MXL_HYDRA_PILOTS_AUTO ; 
 int /*<<< orphan*/  MXL_HYDRA_PILOTS_OFF ; 
 void* MXL_HYDRA_ROLLOFF_0_35 ; 
 void* MXL_HYDRA_ROLLOFF_AUTO ; 
 int /*<<< orphan*/  MXL_HYDRA_SPECTRUM_AUTO ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  cfg_scrambler (struct mxl*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int send_command (struct mxl*,int,int*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int set_parameters(struct dvb_frontend *fe)
{
	struct mxl *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct MXL_HYDRA_DEMOD_PARAM_T demod_chan_cfg;
	u8 cmd_size = sizeof(demod_chan_cfg);
	u8 cmd_buff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
	u32 srange = 10;
	int stat;

	if (p->frequency < 950000 || p->frequency > 2150000)
		return -EINVAL;
	if (p->symbol_rate < 1000000 || p->symbol_rate > 45000000)
		return -EINVAL;

	/* CfgDemodAbortTune(state); */

	switch (p->delivery_system) {
	case SYS_DSS:
		demod_chan_cfg.standard = MXL_HYDRA_DSS;
		demod_chan_cfg.roll_off = MXL_HYDRA_ROLLOFF_AUTO;
		break;
	case SYS_DVBS:
		srange = p->symbol_rate / 1000000;
		if (srange > 10)
			srange = 10;
		demod_chan_cfg.standard = MXL_HYDRA_DVBS;
		demod_chan_cfg.roll_off = MXL_HYDRA_ROLLOFF_0_35;
		demod_chan_cfg.modulation_scheme = MXL_HYDRA_MOD_QPSK;
		demod_chan_cfg.pilots = MXL_HYDRA_PILOTS_OFF;
		break;
	case SYS_DVBS2:
		demod_chan_cfg.standard = MXL_HYDRA_DVBS2;
		demod_chan_cfg.roll_off = MXL_HYDRA_ROLLOFF_AUTO;
		demod_chan_cfg.modulation_scheme = MXL_HYDRA_MOD_AUTO;
		demod_chan_cfg.pilots = MXL_HYDRA_PILOTS_AUTO;
		cfg_scrambler(state, p->scrambling_sequence_index);
		break;
	default:
		return -EINVAL;
	}
	demod_chan_cfg.tuner_index = state->tuner;
	demod_chan_cfg.demod_index = state->demod;
	demod_chan_cfg.frequency_in_hz = p->frequency * 1000;
	demod_chan_cfg.symbol_rate_in_hz = p->symbol_rate;
	demod_chan_cfg.max_carrier_offset_in_mhz = srange;
	demod_chan_cfg.spectrum_inversion = MXL_HYDRA_SPECTRUM_AUTO;
	demod_chan_cfg.fec_code_rate = MXL_HYDRA_FEC_AUTO;

	mutex_lock(&state->base->tune_lock);
	if (time_after(jiffies + msecs_to_jiffies(200),
		       state->base->next_tune))
		while (time_before(jiffies, state->base->next_tune))
			usleep_range(10000, 11000);
	state->base->next_tune = jiffies + msecs_to_jiffies(100);
	state->tuner_in_use = state->tuner;
	BUILD_HYDRA_CMD(MXL_HYDRA_DEMOD_SET_PARAM_CMD, MXL_CMD_WRITE,
			cmd_size, &demod_chan_cfg, cmd_buff);
	stat = send_command(state, cmd_size + MXL_HYDRA_CMD_HEADER_SIZE,
			    &cmd_buff[0]);
	mutex_unlock(&state->base->tune_lock);
	return stat;
}