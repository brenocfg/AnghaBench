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
struct stv0900_state {int /*<<< orphan*/  demod; int /*<<< orphan*/  internal; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
struct dvb_diseqc_master_cmd {int /*<<< orphan*/  msg_len; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int stv0900_diseqc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0900_send_master_cmd(struct dvb_frontend *fe,
					struct dvb_diseqc_master_cmd *cmd)
{
	struct stv0900_state *state = fe->demodulator_priv;

	return stv0900_diseqc_send(state->internal,
				cmd->msg,
				cmd->msg_len,
				state->demod);
}