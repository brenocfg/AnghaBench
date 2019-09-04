#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stv0367_state {int activedemod; } ;
struct TYPE_8__ {TYPE_3__* stat; } ;
struct TYPE_6__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_4__ block_error; TYPE_2__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct stv0367_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_7__ {void* scale; } ;
struct TYPE_5__ {void* scale; } ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
#define  demod_cab 129 
#define  demod_ter 128 
 int stv0367cab_read_status (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  stv0367ddb_read_signal_strength (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stv0367ddb_read_snr (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stv0367ddb_read_ucblocks (struct dvb_frontend*) ; 
 int stv0367ter_read_status (struct dvb_frontend*,int*) ; 

__attribute__((used)) static int stv0367ddb_read_status(struct dvb_frontend *fe,
				  enum fe_status *status)
{
	struct stv0367_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	int ret = 0;

	switch (state->activedemod) {
	case demod_ter:
		ret = stv0367ter_read_status(fe, status);
		break;
	case demod_cab:
		ret = stv0367cab_read_status(fe, status);
		break;
	default:
		break;
	}

	/* stop and report on *_read_status failure */
	if (ret)
		return ret;

	stv0367ddb_read_signal_strength(fe);

	/* read carrier/noise when a carrier is detected */
	if (*status & FE_HAS_CARRIER)
		stv0367ddb_read_snr(fe);
	else
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* read uncorrected blocks on FE_HAS_LOCK */
	if (*status & FE_HAS_LOCK)
		stv0367ddb_read_ucblocks(fe);
	else
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	return 0;
}