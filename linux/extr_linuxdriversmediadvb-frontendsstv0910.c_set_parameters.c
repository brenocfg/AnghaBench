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
struct stv {int /*<<< orphan*/  symbol_rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  symbol_rate; } ;
struct dvb_frontend {TYPE_2__ ops; struct dtv_frontend_properties dtv_property_cache; struct stv* demodulator_priv; } ;

/* Variables and functions */
 int start (struct stv*,struct dtv_frontend_properties*) ; 
 int /*<<< orphan*/  stop (struct stv*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int set_parameters(struct dvb_frontend *fe)
{
	int stat = 0;
	struct stv *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;

	stop(state);
	if (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);
	state->symbol_rate = p->symbol_rate;
	stat = start(state, p);
	return stat;
}