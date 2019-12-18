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
typedef  int /*<<< orphan*/  u32 ;
struct stv0367_state {int activedemod; } ;
struct TYPE_4__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ block_error; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct stv0367_state* demodulator_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  uvalue; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_SCALE_COUNTER ; 
 int /*<<< orphan*/  FE_SCALE_NOT_AVAILABLE ; 
#define  demod_cab 129 
#define  demod_ter 128 
 int /*<<< orphan*/  stv0367cab_read_ucblcks (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stv0367ter_read_ucblocks (struct dvb_frontend*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stv0367ddb_read_ucblocks(struct dvb_frontend *fe)
{
	struct stv0367_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 ucblocks = 0;

	switch (state->activedemod) {
	case demod_ter:
		stv0367ter_read_ucblocks(fe, &ucblocks);
		break;
	case demod_cab:
		stv0367cab_read_ucblcks(fe, &ucblocks);
		break;
	default:
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		return;
	}

	p->block_error.stat[0].scale = FE_SCALE_COUNTER;
	p->block_error.stat[0].uvalue = ucblocks;
}