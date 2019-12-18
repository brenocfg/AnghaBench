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
typedef  int u16 ;
struct sp8870_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int bandwidth_hz; scalar_t__ transmission_mode; } ;
struct dvb_frontend {TYPE_2__ ops; struct sp8870_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 scalar_t__ TRANSMISSION_MODE_2K ; 
 int configure_reg0xc05 (struct dtv_frontend_properties*,int*) ; 
 int /*<<< orphan*/  sp8870_microcontroller_start (struct sp8870_state*) ; 
 int /*<<< orphan*/  sp8870_microcontroller_stop (struct sp8870_state*) ; 
 int sp8870_readreg (struct sp8870_state*,int) ; 
 int /*<<< orphan*/  sp8870_writereg (struct sp8870_state*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sp8870_set_frontend_parameters(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct sp8870_state* state = fe->demodulator_priv;
	int  err;
	u16 reg0xc05;

	if ((err = configure_reg0xc05(p, &reg0xc05)))
		return err;

	// system controller stop
	sp8870_microcontroller_stop(state);

	// set tuner parameters
	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	// sample rate correction bit [23..17]
	sp8870_writereg(state, 0x0319, 0x000A);

	// sample rate correction bit [16..0]
	sp8870_writereg(state, 0x031A, 0x0AAB);

	// integer carrier offset
	sp8870_writereg(state, 0x0309, 0x0400);

	// fractional carrier offset
	sp8870_writereg(state, 0x030A, 0x0000);

	// filter for 6/7/8 Mhz channel
	if (p->bandwidth_hz == 6000000)
		sp8870_writereg(state, 0x0311, 0x0002);
	else if (p->bandwidth_hz == 7000000)
		sp8870_writereg(state, 0x0311, 0x0001);
	else
		sp8870_writereg(state, 0x0311, 0x0000);

	// scan order: 2k first = 0x0000, 8k first = 0x0001
	if (p->transmission_mode == TRANSMISSION_MODE_2K)
		sp8870_writereg(state, 0x0338, 0x0000);
	else
		sp8870_writereg(state, 0x0338, 0x0001);

	sp8870_writereg(state, 0xc05, reg0xc05);

	// read status reg in order to clear pending irqs
	err = sp8870_readreg(state, 0x200);
	if (err)
		return err;

	// system controller start
	sp8870_microcontroller_start(state);

	return 0;
}