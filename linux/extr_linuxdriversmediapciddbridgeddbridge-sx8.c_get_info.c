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
struct sx8 {int /*<<< orphan*/  signal_info; TYPE_1__ mci; } ;
struct mci_command {int /*<<< orphan*/  demod; int /*<<< orphan*/  command; } ;
struct dvb_frontend {struct sx8* demodulator_priv; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_CMD_GETSIGNALINFO ; 
 int ddb_mci_cmd (TYPE_1__*,struct mci_command*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mci_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_info(struct dvb_frontend *fe)
{
	int stat;
	struct sx8 *state = fe->demodulator_priv;
	struct mci_command cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.command = MCI_CMD_GETSIGNALINFO;
	cmd.demod = state->mci.demod;
	stat = ddb_mci_cmd(&state->mci, &cmd, &state->signal_info);
	return stat;
}