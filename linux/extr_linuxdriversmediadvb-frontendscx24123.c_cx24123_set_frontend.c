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
struct TYPE_4__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_5__ {TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {TYPE_2__ ops; struct dtv_frontend_properties dtv_property_cache; struct cx24123_state* demodulator_priv; } ;
struct cx24123_state {TYPE_3__* config; int /*<<< orphan*/  currentsymbolrate; int /*<<< orphan*/  currentfreq; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* agc_callback ) (struct dvb_frontend*) ;int /*<<< orphan*/  dont_use_pll; int /*<<< orphan*/  (* set_ts_params ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cx24123_pll_tune (struct dvb_frontend*) ; 
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int /*<<< orphan*/  cx24123_set_fec (struct cx24123_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx24123_set_inversion (struct cx24123_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx24123_set_symbolrate (struct cx24123_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx24123_writereg (struct cx24123_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*) ; 

__attribute__((used)) static int cx24123_set_frontend(struct dvb_frontend *fe)
{
	struct cx24123_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;

	dprintk("\n");

	if (state->config->set_ts_params)
		state->config->set_ts_params(fe, 0);

	state->currentfreq = p->frequency;
	state->currentsymbolrate = p->symbol_rate;

	cx24123_set_inversion(state, p->inversion);
	cx24123_set_fec(state, p->fec_inner);
	cx24123_set_symbolrate(state, p->symbol_rate);

	if (!state->config->dont_use_pll)
		cx24123_pll_tune(fe);
	else if (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);
	else
		err("it seems I don't have a tuner...");

	/* Enable automatic acquisition and reset cycle */
	cx24123_writereg(state, 0x03, (cx24123_readreg(state, 0x03) | 0x07));
	cx24123_writereg(state, 0x00, 0x10);
	cx24123_writereg(state, 0x00, 0);

	if (state->config->agc_callback)
		state->config->agc_callback(fe);

	return 0;
}