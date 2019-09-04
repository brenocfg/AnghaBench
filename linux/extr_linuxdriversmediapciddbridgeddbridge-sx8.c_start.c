#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sx8_base {int iq_mode; int* used_ldpc_bitrate; int* demod_in_use; int /*<<< orphan*/ * tuner_use_count; scalar_t__ direct_mode; } ;
struct TYPE_5__ {int tuner; int nr; int demod; struct mci_base* base; } ;
struct sx8 {TYPE_2__ mci; } ;
struct TYPE_4__ {int flags; int s2_modulation_mask; int retry; int frequency; int symbol_rate; int scrambling_sequence_index; int input_stream_id; } ;
struct mci_command {int demod; int output; int tuner; TYPE_1__ dvbs2_search; int /*<<< orphan*/  command; } ;
struct mci_base {int /*<<< orphan*/  dev; int /*<<< orphan*/  tuner_lock; } ;
struct dtv_frontend_properties {int symbol_rate; int stream_id; int frequency; int scrambling_sequence_index; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct sx8* demodulator_priv; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MAX_DEMOD_LDPC_BITRATE ; 
 int MAX_LDPC_BITRATE ; 
 int /*<<< orphan*/  MCI_CMD_SEARCH_DVBS ; 
 int MCLK ; 
 int NO_STREAM_ID_FILTER ; 
 int /*<<< orphan*/  SX8_CMD_ENABLE_IQOUTPUT ; 
 int SX8_DEMOD_NUM ; 
 int SX8_TSCONFIG_MODE_MASK ; 
 int SX8_TSCONFIG_MODE_NORMAL ; 
 int ddb_mci_cmd (TYPE_2__*,struct mci_command*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddb_mci_config (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,int,int) ; 
 int /*<<< orphan*/  mci_set_tuner (struct dvb_frontend*,int,int) ; 
 int /*<<< orphan*/  memset (struct mci_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop (struct dvb_frontend*) ; 

__attribute__((used)) static int start(struct dvb_frontend *fe, u32 flags, u32 modmask, u32 ts_config)
{
	struct sx8 *state = fe->demodulator_priv;
	struct mci_base *mci_base = state->mci.base;
	struct sx8_base *sx8_base = (struct sx8_base *)mci_base;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 used_ldpc_bitrate = 0, free_ldpc_bitrate;
	u32 used_demods = 0;
	struct mci_command cmd;
	u32 input = state->mci.tuner;
	u32 bits_per_symbol = 0;
	int i = -1, stat = 0;

	if (p->symbol_rate >= (MCLK / 2))
		flags &= ~1;
	if ((flags & 3) == 0)
		return -EINVAL;

	if (flags & 2) {
		u32 tmp = modmask;

		bits_per_symbol = 1;
		while (tmp & 1) {
			tmp >>= 1;
			bits_per_symbol++;
		}
	}

	mutex_lock(&mci_base->tuner_lock);
	if (sx8_base->iq_mode) {
		stat = -EBUSY;
		goto unlock;
	}

	if (sx8_base->direct_mode) {
		if (p->symbol_rate >= MCLK / 2) {
			if (state->mci.nr < 4)
				i = state->mci.nr;
		} else {
			i = state->mci.nr;
		}
	} else {
		for (i = 0; i < SX8_DEMOD_NUM; i++) {
			used_ldpc_bitrate += sx8_base->used_ldpc_bitrate[i];
			if (sx8_base->demod_in_use[i])
				used_demods++;
		}
		if (used_ldpc_bitrate >= MAX_LDPC_BITRATE ||
		    ((ts_config & SX8_TSCONFIG_MODE_MASK) >
		     SX8_TSCONFIG_MODE_NORMAL && used_demods > 0)) {
			stat = -EBUSY;
			goto unlock;
		}
		free_ldpc_bitrate = MAX_LDPC_BITRATE - used_ldpc_bitrate;
		if (free_ldpc_bitrate > MAX_DEMOD_LDPC_BITRATE)
			free_ldpc_bitrate = MAX_DEMOD_LDPC_BITRATE;

		while (p->symbol_rate * bits_per_symbol > free_ldpc_bitrate)
			bits_per_symbol--;
		if (bits_per_symbol < 2) {
			stat = -EBUSY;
			goto unlock;
		}

		modmask &= ((1 << (bits_per_symbol - 1)) - 1);
		if (((flags & 0x02) != 0) && modmask == 0) {
			stat = -EBUSY;
			goto unlock;
		}

		i = (p->symbol_rate > (MCLK / 2)) ? 3 : 7;
		while (i >= 0 && sx8_base->demod_in_use[i])
			i--;
	}

	if (i < 0) {
		stat = -EBUSY;
		goto unlock;
	}
	sx8_base->demod_in_use[i] = 1;
	sx8_base->used_ldpc_bitrate[state->mci.nr] = p->symbol_rate
						     * bits_per_symbol;
	state->mci.demod = i;

	if (!sx8_base->tuner_use_count[input])
		mci_set_tuner(fe, input, 1);
	sx8_base->tuner_use_count[input]++;
	sx8_base->iq_mode = (ts_config > 1);
unlock:
	mutex_unlock(&mci_base->tuner_lock);
	if (stat)
		return stat;
	memset(&cmd, 0, sizeof(cmd));

	if (sx8_base->iq_mode) {
		cmd.command = SX8_CMD_ENABLE_IQOUTPUT;
		cmd.demod = state->mci.demod;
		cmd.output = 0;
		ddb_mci_cmd(&state->mci, &cmd, NULL);
		ddb_mci_config(&state->mci, ts_config);
	}
	if (p->stream_id != NO_STREAM_ID_FILTER && p->stream_id != 0x80000000)
		flags |= 0x80;
	dev_dbg(mci_base->dev, "MCI-%d: tuner=%d demod=%d\n",
		state->mci.nr, state->mci.tuner, state->mci.demod);
	cmd.command = MCI_CMD_SEARCH_DVBS;
	cmd.dvbs2_search.flags = flags;
	cmd.dvbs2_search.s2_modulation_mask = modmask;
	cmd.dvbs2_search.retry = 2;
	cmd.dvbs2_search.frequency = p->frequency * 1000;
	cmd.dvbs2_search.symbol_rate = p->symbol_rate;
	cmd.dvbs2_search.scrambling_sequence_index =
		p->scrambling_sequence_index | 0x80000000;
	cmd.dvbs2_search.input_stream_id =
		(p->stream_id != NO_STREAM_ID_FILTER) ? p->stream_id : 0;
	cmd.tuner = state->mci.tuner;
	cmd.demod = state->mci.demod;
	cmd.output = state->mci.nr;
	if (p->stream_id == 0x80000000)
		cmd.output |= 0x80;
	stat = ddb_mci_cmd(&state->mci, &cmd, NULL);
	if (stat)
		stop(fe);
	return stat;
}