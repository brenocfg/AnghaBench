#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct dvb_frontend {struct cx24117_state* demodulator_priv; } ;
struct dtv_frontend_properties {scalar_t__ delivery_system; unsigned int frequency; scalar_t__ symbol_rate; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  modulation; int /*<<< orphan*/  inversion; } ;
struct TYPE_3__ {scalar_t__ symbol_rate; } ;
struct cx24117_state {scalar_t__ demod; TYPE_1__ dcur; } ;
struct cx24117_cmd {int* args; int len; } ;
struct TYPE_4__ {int /*<<< orphan*/  fec; int /*<<< orphan*/  modulation; } ;

/* Variables and functions */
 int CMD_GETCTLACC ; 
 int CX24117_REG_FREQ3_0 ; 
 int CX24117_REG_FREQ3_1 ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 scalar_t__ SYS_DVBS2 ; 
 int cx24117_cmd_execute (struct dvb_frontend*,struct cx24117_cmd*) ; 
 TYPE_2__* cx24117_modfec_modes ; 
 int cx24117_readregN (struct cx24117_state*,int,int*,int) ; 

__attribute__((used)) static int cx24117_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *c)
{
	struct cx24117_state *state = fe->demodulator_priv;
	struct cx24117_cmd cmd;
	u8 reg, st, inv;
	int ret, idx;
	unsigned int freq;
	short srate_os, freq_os;

	u8 buf[0x1f-4];

	/* Read current tune parameters */
	cmd.args[0] = CMD_GETCTLACC;
	cmd.args[1] = (u8) state->demod;
	cmd.len = 2;
	ret = cx24117_cmd_execute(fe, &cmd);
	if (ret != 0)
		return ret;

	/* read all required regs at once */
	reg = (state->demod == 0) ? CX24117_REG_FREQ3_0 : CX24117_REG_FREQ3_1;
	ret = cx24117_readregN(state, reg, buf, 0x1f-4);
	if (ret != 0)
		return ret;

	st = buf[5];

	/* get spectral inversion */
	inv = (((state->demod == 0) ? ~st : st) >> 6) & 1;
	if (inv == 0)
		c->inversion = INVERSION_OFF;
	else
		c->inversion = INVERSION_ON;

	/* modulation and fec */
	idx = st & 0x3f;
	if (c->delivery_system == SYS_DVBS2) {
		if (idx > 11)
			idx += 9;
		else
			idx += 7;
	}

	c->modulation = cx24117_modfec_modes[idx].modulation;
	c->fec_inner = cx24117_modfec_modes[idx].fec;

	/* frequency */
	freq = (buf[0] << 16) | (buf[1] << 8) | buf[2];
	freq_os = (buf[8] << 8) | buf[9];
	c->frequency = freq + freq_os;

	/* symbol rate */
	srate_os = (buf[10] << 8) | buf[11];
	c->symbol_rate = -1000 * srate_os + state->dcur.symbol_rate;
	return 0;
}