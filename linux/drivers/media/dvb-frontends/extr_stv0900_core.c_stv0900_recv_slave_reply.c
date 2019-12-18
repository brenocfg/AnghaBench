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
struct stv0900_state {int demod; struct stv0900_internal* internal; } ;
struct stv0900_internal {int dummy; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
struct dvb_diseqc_slave_reply {int msg_len; int /*<<< orphan*/ * msg; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  DISRXDATA ; 
 int /*<<< orphan*/  FIFO_BYTENBR ; 
 int /*<<< orphan*/  RX_END ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_read_reg (struct stv0900_internal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0900_recv_slave_reply(struct dvb_frontend *fe,
				struct dvb_diseqc_slave_reply *reply)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_demod_num demod = state->demod;
	s32 i = 0;

	reply->msg_len = 0;

	while ((stv0900_get_bits(intp, RX_END) != 1) && (i < 10)) {
		msleep(10);
		i++;
	}

	if (stv0900_get_bits(intp, RX_END)) {
		reply->msg_len = stv0900_get_bits(intp, FIFO_BYTENBR);

		for (i = 0; i < reply->msg_len; i++)
			reply->msg[i] = stv0900_read_reg(intp, DISRXDATA);
	}

	return 0;
}