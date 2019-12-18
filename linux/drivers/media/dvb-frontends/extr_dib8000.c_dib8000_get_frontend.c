#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dtv_frontend_properties {int bandwidth_hz; int isdbt_sb_mode; int inversion; int isdbt_partial_reception; TYPE_4__* layer; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; } ;
struct dib8000_state {int revision; TYPE_5__** fe; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_9__ {int isdbt_sb_mode; int inversion; int isdbt_partial_reception; TYPE_2__* layer; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_frontend ) (TYPE_5__*,struct dtv_frontend_properties*) ;int /*<<< orphan*/  (* read_status ) (TYPE_5__*,int*) ;} ;
struct TYPE_11__ {TYPE_3__ dtv_property_cache; TYPE_1__ ops; } ;
struct TYPE_10__ {int segment_count; int interleaving; int /*<<< orphan*/  modulation; int /*<<< orphan*/  fec; } ;
struct TYPE_8__ {int segment_count; int interleaving; int /*<<< orphan*/  modulation; int /*<<< orphan*/  fec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQPSK ; 
 int /*<<< orphan*/  FEC_1_2 ; 
 int /*<<< orphan*/  FEC_2_3 ; 
 int /*<<< orphan*/  FEC_3_4 ; 
 int /*<<< orphan*/  FEC_5_6 ; 
 int /*<<< orphan*/  FEC_7_8 ; 
 int FE_HAS_SYNC ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 size_t MAX_NUMBER_OF_FRONTENDS ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_4K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  dib8000_read_status (struct dvb_frontend*,int*) ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,struct dtv_frontend_properties*) ; 

__attribute__((used)) static int dib8000_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *c)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 i, val = 0;
	enum fe_status stat = 0;
	u8 index_frontend, sub_index_frontend;

	c->bandwidth_hz = 6000000;

	/*
	 * If called to early, get_frontend makes dib8000_tune to either
	 * not lock or not sync. This causes dvbv5-scan/dvbv5-zap to fail.
	 * So, let's just return if frontend 0 has not locked.
	 */
	dib8000_read_status(fe, &stat);
	if (!(stat & FE_HAS_SYNC))
		return 0;

	dprintk("dib8000_get_frontend: TMCC lock\n");
	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
		state->fe[index_frontend]->ops.read_status(state->fe[index_frontend], &stat);
		if (stat&FE_HAS_SYNC) {
			dprintk("TMCC lock on the slave%i\n", index_frontend);
			/* synchronize the cache with the other frontends */
			state->fe[index_frontend]->ops.get_frontend(state->fe[index_frontend], c);
			for (sub_index_frontend = 0; (sub_index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[sub_index_frontend] != NULL); sub_index_frontend++) {
				if (sub_index_frontend != index_frontend) {
					state->fe[sub_index_frontend]->dtv_property_cache.isdbt_sb_mode = state->fe[index_frontend]->dtv_property_cache.isdbt_sb_mode;
					state->fe[sub_index_frontend]->dtv_property_cache.inversion = state->fe[index_frontend]->dtv_property_cache.inversion;
					state->fe[sub_index_frontend]->dtv_property_cache.transmission_mode = state->fe[index_frontend]->dtv_property_cache.transmission_mode;
					state->fe[sub_index_frontend]->dtv_property_cache.guard_interval = state->fe[index_frontend]->dtv_property_cache.guard_interval;
					state->fe[sub_index_frontend]->dtv_property_cache.isdbt_partial_reception = state->fe[index_frontend]->dtv_property_cache.isdbt_partial_reception;
					for (i = 0; i < 3; i++) {
						state->fe[sub_index_frontend]->dtv_property_cache.layer[i].segment_count = state->fe[index_frontend]->dtv_property_cache.layer[i].segment_count;
						state->fe[sub_index_frontend]->dtv_property_cache.layer[i].interleaving = state->fe[index_frontend]->dtv_property_cache.layer[i].interleaving;
						state->fe[sub_index_frontend]->dtv_property_cache.layer[i].fec = state->fe[index_frontend]->dtv_property_cache.layer[i].fec;
						state->fe[sub_index_frontend]->dtv_property_cache.layer[i].modulation = state->fe[index_frontend]->dtv_property_cache.layer[i].modulation;
					}
				}
			}
			return 0;
		}
	}

	c->isdbt_sb_mode = dib8000_read_word(state, 508) & 0x1;

	if (state->revision == 0x8090)
		val = dib8000_read_word(state, 572);
	else
		val = dib8000_read_word(state, 570);
	c->inversion = (val & 0x40) >> 6;
	switch ((val & 0x30) >> 4) {
	case 1:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		dprintk("dib8000_get_frontend: transmission mode 2K\n");
		break;
	case 2:
		c->transmission_mode = TRANSMISSION_MODE_4K;
		dprintk("dib8000_get_frontend: transmission mode 4K\n");
		break;
	case 3:
	default:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		dprintk("dib8000_get_frontend: transmission mode 8K\n");
		break;
	}

	switch (val & 0x3) {
	case 0:
		c->guard_interval = GUARD_INTERVAL_1_32;
		dprintk("dib8000_get_frontend: Guard Interval = 1/32\n");
		break;
	case 1:
		c->guard_interval = GUARD_INTERVAL_1_16;
		dprintk("dib8000_get_frontend: Guard Interval = 1/16\n");
		break;
	case 2:
		dprintk("dib8000_get_frontend: Guard Interval = 1/8\n");
		c->guard_interval = GUARD_INTERVAL_1_8;
		break;
	case 3:
		dprintk("dib8000_get_frontend: Guard Interval = 1/4\n");
		c->guard_interval = GUARD_INTERVAL_1_4;
		break;
	}

	val = dib8000_read_word(state, 505);
	c->isdbt_partial_reception = val & 1;
	dprintk("dib8000_get_frontend: partial_reception = %d\n", c->isdbt_partial_reception);

	for (i = 0; i < 3; i++) {
		int show;

		val = dib8000_read_word(state, 493 + i) & 0x0f;
		c->layer[i].segment_count = val;

		if (val == 0 || val > 13)
			show = 0;
		else
			show = 1;

		if (show)
			dprintk("dib8000_get_frontend: Layer %d segments = %d\n",
				i, c->layer[i].segment_count);

		val = dib8000_read_word(state, 499 + i) & 0x3;
		/* Interleaving can be 0, 1, 2 or 4 */
		if (val == 3)
			val = 4;
		c->layer[i].interleaving = val;
		if (show)
			dprintk("dib8000_get_frontend: Layer %d time_intlv = %d\n",
				i, c->layer[i].interleaving);

		val = dib8000_read_word(state, 481 + i);
		switch (val & 0x7) {
		case 1:
			c->layer[i].fec = FEC_1_2;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d Code Rate = 1/2\n", i);
			break;
		case 2:
			c->layer[i].fec = FEC_2_3;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d Code Rate = 2/3\n", i);
			break;
		case 3:
			c->layer[i].fec = FEC_3_4;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d Code Rate = 3/4\n", i);
			break;
		case 5:
			c->layer[i].fec = FEC_5_6;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d Code Rate = 5/6\n", i);
			break;
		default:
			c->layer[i].fec = FEC_7_8;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d Code Rate = 7/8\n", i);
			break;
		}

		val = dib8000_read_word(state, 487 + i);
		switch (val & 0x3) {
		case 0:
			c->layer[i].modulation = DQPSK;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d DQPSK\n", i);
			break;
		case 1:
			c->layer[i].modulation = QPSK;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d QPSK\n", i);
			break;
		case 2:
			c->layer[i].modulation = QAM_16;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d QAM16\n", i);
			break;
		case 3:
		default:
			c->layer[i].modulation = QAM_64;
			if (show)
				dprintk("dib8000_get_frontend: Layer %d QAM64\n", i);
			break;
		}
	}

	/* synchronize the cache with the other frontends */
	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
		state->fe[index_frontend]->dtv_property_cache.isdbt_sb_mode = c->isdbt_sb_mode;
		state->fe[index_frontend]->dtv_property_cache.inversion = c->inversion;
		state->fe[index_frontend]->dtv_property_cache.transmission_mode = c->transmission_mode;
		state->fe[index_frontend]->dtv_property_cache.guard_interval = c->guard_interval;
		state->fe[index_frontend]->dtv_property_cache.isdbt_partial_reception = c->isdbt_partial_reception;
		for (i = 0; i < 3; i++) {
			state->fe[index_frontend]->dtv_property_cache.layer[i].segment_count = c->layer[i].segment_count;
			state->fe[index_frontend]->dtv_property_cache.layer[i].interleaving = c->layer[i].interleaving;
			state->fe[index_frontend]->dtv_property_cache.layer[i].fec = c->layer[i].fec;
			state->fe[index_frontend]->dtv_property_cache.layer[i].modulation = c->layer[i].modulation;
		}
	}
	return 0;
}