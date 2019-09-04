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
struct stv0367_state {int activedemod; } ;
struct TYPE_4__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct stv0367_state* demodulator_priv; } ;
typedef  int s32 ;
struct TYPE_3__ {int uvalue; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_SCALE_DECIBEL ; 
 int /*<<< orphan*/  FE_SCALE_NOT_AVAILABLE ; 
#define  demod_cab 128 
 int stv0367cab_get_rf_lvl (struct stv0367_state*) ; 

__attribute__((used)) static void stv0367ddb_read_signal_strength(struct dvb_frontend *fe)
{
	struct stv0367_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	s32 signalstrength;

	switch (state->activedemod) {
	case demod_cab:
		signalstrength = stv0367cab_get_rf_lvl(state) * 1000;
		break;
	default:
		p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		return;
	}

	p->strength.stat[0].scale = FE_SCALE_DECIBEL;
	p->strength.stat[0].uvalue = signalstrength;
}