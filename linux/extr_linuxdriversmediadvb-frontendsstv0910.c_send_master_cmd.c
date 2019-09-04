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
struct stv {int dummy; } ;
struct dvb_frontend {struct stv* demodulator_priv; } ;
struct dvb_diseqc_master_cmd {int msg_len; int /*<<< orphan*/ * msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISEQC_MODE ; 
 int /*<<< orphan*/  DISTXFIFO ; 
 int /*<<< orphan*/  DIS_PRECHARGE ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_dis (struct stv*,int,int) ; 

__attribute__((used)) static int send_master_cmd(struct dvb_frontend *fe,
			   struct dvb_diseqc_master_cmd *cmd)
{
	struct stv *state = fe->demodulator_priv;
	int i;

	SET_FIELD(DISEQC_MODE, 2);
	SET_FIELD(DIS_PRECHARGE, 1);
	for (i = 0; i < cmd->msg_len; i++) {
		wait_dis(state, 0x40, 0x00);
		SET_REG(DISTXFIFO, cmd->msg[i]);
	}
	SET_FIELD(DIS_PRECHARGE, 0);
	wait_dis(state, 0x20, 0x20);
	return 0;
}