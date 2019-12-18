#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sx8_base {scalar_t__ iq_mode; scalar_t__* used_ldpc_bitrate; scalar_t__* demod_in_use; int /*<<< orphan*/ * tuner_use_count; } ;
struct TYPE_3__ {size_t tuner; size_t demod; size_t nr; struct mci_base* base; } ;
struct sx8 {scalar_t__ started; TYPE_1__ mci; } ;
struct mci_command {size_t demod; scalar_t__ output; int /*<<< orphan*/  command; } ;
struct mci_base {int /*<<< orphan*/  tuner_lock; } ;
struct dvb_frontend {struct sx8* demodulator_priv; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_CMD_STOP ; 
 int /*<<< orphan*/  SX8_CMD_DISABLE_IQOUTPUT ; 
 size_t SX8_DEMOD_NONE ; 
 size_t SX8_DEMOD_NUM ; 
 int /*<<< orphan*/  SX8_TSCONFIG_MODE_NORMAL ; 
 int /*<<< orphan*/  ddb_mci_cmd (TYPE_1__*,struct mci_command*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddb_mci_config (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_set_tuner (struct dvb_frontend*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mci_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stop(struct dvb_frontend *fe)
{
	struct sx8 *state = fe->demodulator_priv;
	struct mci_base *mci_base = state->mci.base;
	struct sx8_base *sx8_base = (struct sx8_base *)mci_base;
	struct mci_command cmd;
	u32 input = state->mci.tuner;

	memset(&cmd, 0, sizeof(cmd));
	if (state->mci.demod != SX8_DEMOD_NONE) {
		cmd.command = MCI_CMD_STOP;
		cmd.demod = state->mci.demod;
		ddb_mci_cmd(&state->mci, &cmd, NULL);
		if (sx8_base->iq_mode) {
			cmd.command = SX8_CMD_DISABLE_IQOUTPUT;
			cmd.demod = state->mci.demod;
			cmd.output = 0;
			ddb_mci_cmd(&state->mci, &cmd, NULL);
			ddb_mci_config(&state->mci, SX8_TSCONFIG_MODE_NORMAL);
		}
	}
	mutex_lock(&mci_base->tuner_lock);
	sx8_base->tuner_use_count[input]--;
	if (!sx8_base->tuner_use_count[input])
		mci_set_tuner(fe, input, 0);
	if (state->mci.demod < SX8_DEMOD_NUM) {
		sx8_base->demod_in_use[state->mci.demod] = 0;
		state->mci.demod = SX8_DEMOD_NONE;
	}
	sx8_base->used_ldpc_bitrate[state->mci.nr] = 0;
	sx8_base->iq_mode = 0;
	mutex_unlock(&mci_base->tuner_lock);
	state->started = 0;
	return 0;
}