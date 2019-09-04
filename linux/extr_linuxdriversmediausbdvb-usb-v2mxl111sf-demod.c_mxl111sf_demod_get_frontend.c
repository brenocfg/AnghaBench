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
struct mxl111sf_demod_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_frequency ) (struct dvb_frontend*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_bandwidth ) (struct dvb_frontend*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct mxl111sf_demod_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  modulation; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  frequency; int /*<<< orphan*/  bandwidth_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxl1x1sf_demod_get_tps_code_rate (struct mxl111sf_demod_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxl1x1sf_demod_get_tps_guard_fft_mode (struct mxl111sf_demod_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxl1x1sf_demod_get_tps_guard_interval (struct mxl111sf_demod_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxl1x1sf_demod_get_tps_hierarchy (struct mxl111sf_demod_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxl1x1sf_demod_get_tps_modulation (struct mxl111sf_demod_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxl_dbg (char*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxl111sf_demod_get_frontend(struct dvb_frontend *fe,
				       struct dtv_frontend_properties *p)
{
	struct mxl111sf_demod_state *state = fe->demodulator_priv;

	mxl_dbg("()");
#if 0
	p->inversion = /* FIXME */ ? INVERSION_ON : INVERSION_OFF;
#endif
	if (fe->ops.tuner_ops.get_bandwidth)
		fe->ops.tuner_ops.get_bandwidth(fe, &p->bandwidth_hz);
	if (fe->ops.tuner_ops.get_frequency)
		fe->ops.tuner_ops.get_frequency(fe, &p->frequency);
	mxl1x1sf_demod_get_tps_code_rate(state, &p->code_rate_HP);
	mxl1x1sf_demod_get_tps_code_rate(state, &p->code_rate_LP);
	mxl1x1sf_demod_get_tps_modulation(state, &p->modulation);
	mxl1x1sf_demod_get_tps_guard_fft_mode(state,
					      &p->transmission_mode);
	mxl1x1sf_demod_get_tps_guard_interval(state,
					      &p->guard_interval);
	mxl1x1sf_demod_get_tps_hierarchy(state,
					 &p->hierarchy);

	return 0;
}