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
struct TYPE_2__ {int /*<<< orphan*/  demod; } ;
struct sx8 {TYPE_1__ mci; } ;
struct mci_result {scalar_t__ status; } ;
struct mci_command {int /*<<< orphan*/  demod; int /*<<< orphan*/  command; } ;
struct dvb_frontend {struct sx8* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_CMD_GETSTATUS ; 
 scalar_t__ SX8_DEMOD_LOCKED ; 
 scalar_t__ SX8_DEMOD_WAIT_MATYPE ; 
 int ddb_mci_cmd (TYPE_1__*,struct mci_command*,struct mci_result*) ; 
 int /*<<< orphan*/  get_info (struct dvb_frontend*) ; 
 int /*<<< orphan*/  get_snr (struct dvb_frontend*) ; 
 int /*<<< orphan*/  get_strength (struct dvb_frontend*) ; 

__attribute__((used)) static int read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	int stat;
	struct sx8 *state = fe->demodulator_priv;
	struct mci_command cmd;
	struct mci_result res;

	cmd.command = MCI_CMD_GETSTATUS;
	cmd.demod = state->mci.demod;
	stat = ddb_mci_cmd(&state->mci, &cmd, &res);
	if (stat)
		return stat;
	*status = 0x00;
	get_info(fe);
	get_strength(fe);
	if (res.status == SX8_DEMOD_WAIT_MATYPE)
		*status = 0x0f;
	if (res.status == SX8_DEMOD_LOCKED) {
		*status = 0x1f;
		get_snr(fe);
	}
	return stat;
}