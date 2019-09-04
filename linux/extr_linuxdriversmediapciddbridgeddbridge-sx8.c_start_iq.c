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
typedef  scalar_t__ u32 ;
struct sx8_base {int iq_mode; int /*<<< orphan*/ * tuner_use_count; scalar_t__* demod_in_use; } ;
struct TYPE_5__ {scalar_t__ tuner; scalar_t__ demod; struct mci_base* base; } ;
struct sx8 {TYPE_2__ mci; } ;
struct TYPE_4__ {int frequency; int /*<<< orphan*/  symbol_rate; scalar_t__ roll_off; scalar_t__ flags; } ;
struct mci_command {scalar_t__ tuner; scalar_t__ demod; TYPE_1__ sx8_start_iq; int /*<<< orphan*/  command; } ;
struct mci_base {int /*<<< orphan*/  tuner_lock; } ;
struct dtv_frontend_properties {int frequency; int /*<<< orphan*/  symbol_rate; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct sx8* demodulator_priv; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SX8_CMD_START_IQ ; 
 int SX8_DEMOD_NUM ; 
 int ddb_mci_cmd (TYPE_2__*,struct mci_command*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddb_mci_config (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  mci_set_tuner (struct dvb_frontend*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct mci_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop (struct dvb_frontend*) ; 

__attribute__((used)) static int start_iq(struct dvb_frontend *fe, u32 flags, u32 roll_off,
		    u32 ts_config)
{
	struct sx8 *state = fe->demodulator_priv;
	struct mci_base *mci_base = state->mci.base;
	struct sx8_base *sx8_base = (struct sx8_base *)mci_base;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 used_demods = 0;
	struct mci_command cmd;
	u32 input = state->mci.tuner;
	int i, stat = 0;

	mutex_lock(&mci_base->tuner_lock);
	if (sx8_base->iq_mode) {
		stat = -EBUSY;
		goto unlock;
	}
	for (i = 0; i < SX8_DEMOD_NUM; i++)
		if (sx8_base->demod_in_use[i])
			used_demods++;
	if (used_demods > 0) {
		stat = -EBUSY;
		goto unlock;
	}
	state->mci.demod = 0;
	if (!sx8_base->tuner_use_count[input])
		mci_set_tuner(fe, input, 1);
	sx8_base->tuner_use_count[input]++;
	sx8_base->iq_mode = (ts_config > 1);
unlock:
	mutex_unlock(&mci_base->tuner_lock);
	if (stat)
		return stat;

	memset(&cmd, 0, sizeof(cmd));
	cmd.command = SX8_CMD_START_IQ;
	cmd.sx8_start_iq.flags = flags;
	cmd.sx8_start_iq.roll_off = roll_off;
	cmd.sx8_start_iq.frequency = p->frequency * 1000;
	cmd.sx8_start_iq.symbol_rate = p->symbol_rate;
	cmd.tuner = state->mci.tuner;
	cmd.demod = state->mci.demod;
	stat = ddb_mci_cmd(&state->mci, &cmd, NULL);
	if (stat)
		stop(fe);
	ddb_mci_config(&state->mci, ts_config);
	return stat;
}