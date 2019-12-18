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
struct dvb_frontend {struct cx24117_state* demodulator_priv; } ;
struct TYPE_2__ {int* args; int len; } ;
struct cx24117_state {TYPE_1__ dsec_cmd; scalar_t__ demod; } ;

/* Variables and functions */
 int CMD_LNBSEND ; 
 size_t CX24117_DISEQC_ARG3_2 ; 
 size_t CX24117_DISEQC_ARG4_0 ; 
 size_t CX24117_DISEQC_ARG5_0 ; 
 size_t CX24117_DISEQC_BURST ; 
 size_t CX24117_DISEQC_DEMOD ; 
 int CX24117_DISEQC_MINI_A ; 
 size_t CX24117_DISEQC_MSGLEN ; 

__attribute__((used)) static int cx24117_diseqc_init(struct dvb_frontend *fe)
{
	struct cx24117_state *state = fe->demodulator_priv;

	/* Prepare a DiSEqC command */
	state->dsec_cmd.args[0] = CMD_LNBSEND;

	/* demod */
	state->dsec_cmd.args[CX24117_DISEQC_DEMOD] = state->demod ? 0 : 1;

	/* DiSEqC burst */
	state->dsec_cmd.args[CX24117_DISEQC_BURST] = CX24117_DISEQC_MINI_A;

	/* Unknown */
	state->dsec_cmd.args[CX24117_DISEQC_ARG3_2] = 0x02;
	state->dsec_cmd.args[CX24117_DISEQC_ARG4_0] = 0x00;

	/* Continuation flag? */
	state->dsec_cmd.args[CX24117_DISEQC_ARG5_0] = 0x00;

	/* DiSEqC message length */
	state->dsec_cmd.args[CX24117_DISEQC_MSGLEN] = 0x00;

	/* Command length */
	state->dsec_cmd.len = 7;

	return 0;
}