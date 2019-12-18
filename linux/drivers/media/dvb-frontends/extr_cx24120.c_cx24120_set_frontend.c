#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dtv_frontend_properties {int delivery_system; int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  pilot; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  modulation; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct cx24120_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_6__ {int frequency; int pilot; int pilot_val; int symbol_rate; int clkdiv; int ratediv; int fec_mask; int fec_val; int inversion; int inversion_val; int /*<<< orphan*/  fec; int /*<<< orphan*/  modulation; int /*<<< orphan*/  delsys; } ;
struct TYPE_4__ {int delsys; int /*<<< orphan*/  pilot; int /*<<< orphan*/  frequency; int /*<<< orphan*/  modulation; } ;
struct cx24120_state {int need_clock_set; TYPE_3__ dcur; TYPE_2__* i2c; TYPE_1__ dnxt; } ;
struct cx24120_cmd {int len; int* arg; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TUNEREQUEST ; 
 int /*<<< orphan*/  CX24120_REG_CLKDIV ; 
 int /*<<< orphan*/  CX24120_REG_RATEDIV ; 
 int CX24120_SEARCH_RANGE_KHZ ; 
 int EINVAL ; 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  cx24120_clone_params (struct dvb_frontend*) ; 
 int cx24120_message_send (struct cx24120_state*,struct cx24120_cmd*) ; 
 int cx24120_readreg (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int cx24120_set_fec (struct cx24120_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cx24120_set_inversion (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int cx24120_set_pilot (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int cx24120_set_symbolrate (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int cx24120_writereg (struct cx24120_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int cx24120_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct cx24120_state *state = fe->demodulator_priv;
	struct cx24120_cmd cmd;
	int ret;

	switch (c->delivery_system) {
	case SYS_DVBS2:
		dev_dbg(&state->i2c->dev, "DVB-S2\n");
		break;
	case SYS_DVBS:
		dev_dbg(&state->i2c->dev, "DVB-S\n");
		break;
	default:
		dev_dbg(&state->i2c->dev,
			"delivery system(%d) not supported\n",
			c->delivery_system);
		return -EINVAL;
	}

	state->dnxt.delsys = c->delivery_system;
	state->dnxt.modulation = c->modulation;
	state->dnxt.frequency = c->frequency;
	state->dnxt.pilot = c->pilot;

	ret = cx24120_set_inversion(state, c->inversion);
	if (ret !=  0)
		return ret;

	ret = cx24120_set_fec(state, c->modulation, c->fec_inner);
	if (ret !=  0)
		return ret;

	ret = cx24120_set_pilot(state, c->pilot);
	if (ret != 0)
		return ret;

	ret = cx24120_set_symbolrate(state, c->symbol_rate);
	if (ret !=  0)
		return ret;

	/* discard the 'current' tuning parameters and prepare to tune */
	cx24120_clone_params(fe);

	dev_dbg(&state->i2c->dev,
		"delsys      = %d\n", state->dcur.delsys);
	dev_dbg(&state->i2c->dev,
		"modulation  = %d\n", state->dcur.modulation);
	dev_dbg(&state->i2c->dev,
		"frequency   = %d\n", state->dcur.frequency);
	dev_dbg(&state->i2c->dev,
		"pilot       = %d (val = 0x%02x)\n",
		state->dcur.pilot, state->dcur.pilot_val);
	dev_dbg(&state->i2c->dev,
		"symbol_rate = %d (clkdiv/ratediv = 0x%02x/0x%02x)\n",
		 state->dcur.symbol_rate,
		 state->dcur.clkdiv, state->dcur.ratediv);
	dev_dbg(&state->i2c->dev,
		"FEC         = %d (mask/val = 0x%02x/0x%02x)\n",
		state->dcur.fec, state->dcur.fec_mask, state->dcur.fec_val);
	dev_dbg(&state->i2c->dev,
		"Inversion   = %d (val = 0x%02x)\n",
		state->dcur.inversion, state->dcur.inversion_val);

	/* Flag that clock needs to be set after tune */
	state->need_clock_set = 1;

	/* Tune in */
	cmd.id = CMD_TUNEREQUEST;
	cmd.len = 15;
	cmd.arg[0] = 0;
	cmd.arg[1]  = (state->dcur.frequency & 0xff0000) >> 16;
	cmd.arg[2]  = (state->dcur.frequency & 0x00ff00) >> 8;
	cmd.arg[3]  = (state->dcur.frequency & 0x0000ff);
	cmd.arg[4]  = ((state->dcur.symbol_rate / 1000) & 0xff00) >> 8;
	cmd.arg[5]  = ((state->dcur.symbol_rate / 1000) & 0x00ff);
	cmd.arg[6]  = state->dcur.inversion;
	cmd.arg[7]  = state->dcur.fec_val | state->dcur.pilot_val;
	cmd.arg[8]  = CX24120_SEARCH_RANGE_KHZ >> 8;
	cmd.arg[9]  = CX24120_SEARCH_RANGE_KHZ & 0xff;
	cmd.arg[10] = 0;		/* maybe rolloff? */
	cmd.arg[11] = state->dcur.fec_mask;
	cmd.arg[12] = state->dcur.ratediv;
	cmd.arg[13] = state->dcur.clkdiv;
	cmd.arg[14] = 0;

	/* Send tune command */
	ret = cx24120_message_send(state, &cmd);
	if (ret != 0)
		return ret;

	/* Write symbol rate values */
	ret = cx24120_writereg(state, CX24120_REG_CLKDIV, state->dcur.clkdiv);
	ret = cx24120_readreg(state, CX24120_REG_RATEDIV);
	ret &= 0xfffffff0;
	ret |= state->dcur.ratediv;
	ret = cx24120_writereg(state, CX24120_REG_RATEDIV, ret);

	return 0;
}