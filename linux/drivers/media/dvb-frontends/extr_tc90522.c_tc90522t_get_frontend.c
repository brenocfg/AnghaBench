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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tc90522_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_rf_strength ) (struct dvb_frontend*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct tc90522_state* demodulator_priv; } ;
struct dtv_fe_stats {int len; TYPE_3__* stat; } ;
struct dtv_frontend_properties {int bandwidth_hz; int guard_interval; int isdbt_partial_reception; int isdbt_sb_mode; struct dtv_fe_stats post_bit_count; struct dtv_fe_stats post_bit_error; struct dtv_fe_stats cnr; struct dtv_fe_stats strength; TYPE_4__* layer; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  delivery_system; } ;
typedef  int s64 ;
struct TYPE_8__ {int segment_count; int interleaving; void* modulation; void* fec; } ;
struct TYPE_7__ {int svalue; int uvalue; void* scale; } ;

/* Variables and functions */
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 int /*<<< orphan*/  SYS_ISDBT ; 
 int div64_s64 (long long,int) ; 
 void** fec_conv_ter ; 
 int intlog10 (int) ; 
 int /*<<< orphan*/  memset (struct dtv_fe_stats*,int /*<<< orphan*/ ,int) ; 
 void** mod_conv ; 
 int reg_read (struct tc90522_state*,int,int*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tm_conv ; 

__attribute__((used)) static int tc90522t_get_frontend(struct dvb_frontend *fe,
				 struct dtv_frontend_properties *c)
{
	struct tc90522_state *state;
	struct dtv_fe_stats *stats;
	int ret, i;
	int layers;
	u8 val[15], mode;
	u32 cndat;

	state = fe->demodulator_priv;
	c->delivery_system = SYS_ISDBT;
	c->bandwidth_hz = 6000000;
	mode = 1;
	ret = reg_read(state, 0xb0, val, 1);
	if (ret == 0) {
		mode = (val[0] & 0xc0) >> 6;
		c->transmission_mode = tm_conv[mode];
		c->guard_interval = (val[0] & 0x30) >> 4;
	}

	ret = reg_read(state, 0xb2, val, 6);
	layers = 0;
	if (ret == 0) {
		u8 v;

		c->isdbt_partial_reception = val[0] & 0x01;
		c->isdbt_sb_mode = (val[0] & 0xc0) == 0x40;

		/* layer A */
		v = (val[2] & 0x78) >> 3;
		if (v == 0x0f)
			c->layer[0].segment_count = 0;
		else {
			layers++;
			c->layer[0].segment_count = v;
			c->layer[0].fec = fec_conv_ter[(val[1] & 0x1c) >> 2];
			c->layer[0].modulation = mod_conv[(val[1] & 0xe0) >> 5];
			v = (val[1] & 0x03) << 1 | (val[2] & 0x80) >> 7;
			c->layer[0].interleaving = v;
		}

		/* layer B */
		v = (val[3] & 0x03) << 2 | (val[4] & 0xc0) >> 6;
		if (v == 0x0f)
			c->layer[1].segment_count = 0;
		else {
			layers++;
			c->layer[1].segment_count = v;
			c->layer[1].fec = fec_conv_ter[(val[3] & 0xe0) >> 5];
			c->layer[1].modulation = mod_conv[(val[2] & 0x07)];
			c->layer[1].interleaving = (val[3] & 0x1c) >> 2;
		}

		/* layer C */
		v = (val[5] & 0x1e) >> 1;
		if (v == 0x0f)
			c->layer[2].segment_count = 0;
		else {
			layers++;
			c->layer[2].segment_count = v;
			c->layer[2].fec = fec_conv_ter[(val[4] & 0x07)];
			c->layer[2].modulation = mod_conv[(val[4] & 0x38) >> 3];
			c->layer[2].interleaving = (val[5] & 0xe0) >> 5;
		}
	}

	/* statistics */

	stats = &c->strength;
	stats->len = 0;
	/* let the connected tuner set RSSI property cache */
	if (fe->ops.tuner_ops.get_rf_strength) {
		u16 dummy;

		fe->ops.tuner_ops.get_rf_strength(fe, &dummy);
	}

	stats = &c->cnr;
	stats->len = 1;
	stats->stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	cndat = 0;
	ret = reg_read(state, 0x8b, val, 3);
	if (ret == 0)
		cndat = val[0] << 16 | val[1] << 8 | val[2];
	if (cndat != 0) {
		u32 p, tmp;
		s64 cn;

		/*
		 * cnr[mdB] = 0.024 P^4 - 1.6 P^3 + 39.8 P^2 + 549.1 P + 3096.5
		 * (P = 10log10(5505024/cndat))
		 */
		/* cn = cnr << 3 (61.3 fixed point float */
		/* p = 10log10(5505024/cndat) << 24  (8.24 fixed point float)*/
		p = intlog10(5505024) - intlog10(cndat);
		p *= 10;

		cn = 24772;
		cn += div64_s64(43827LL * p, 10) >> 24;
		tmp = p >> 8;
		cn += div64_s64(3184LL * tmp * tmp, 10) >> 32;
		tmp = p >> 13;
		cn -= div64_s64(128LL * tmp * tmp * tmp, 10) >> 33;
		tmp = p >> 18;
		cn += div64_s64(192LL * tmp * tmp * tmp * tmp, 1000) >> 24;

		stats->stat[0].svalue = cn >> 3;
		stats->stat[0].scale = FE_SCALE_DECIBEL;
	}

	/* per-layer post viterbi BER (or PER? config dependent?) */
	stats = &c->post_bit_error;
	memset(stats, 0, sizeof(*stats));
	stats->len = layers;
	ret = reg_read(state, 0x9d, val, 15);
	if (ret < 0)
		for (i = 0; i < layers; i++)
			stats->stat[i].scale = FE_SCALE_NOT_AVAILABLE;
	else {
		for (i = 0; i < layers; i++) {
			stats->stat[i].scale = FE_SCALE_COUNTER;
			stats->stat[i].uvalue = val[i * 3] << 16
				| val[i * 3 + 1] << 8 | val[i * 3 + 2];
		}
	}
	stats = &c->post_bit_count;
	memset(stats, 0, sizeof(*stats));
	stats->len = layers;
	if (ret < 0)
		for (i = 0; i < layers; i++)
			stats->stat[i].scale = FE_SCALE_NOT_AVAILABLE;
	else {
		for (i = 0; i < layers; i++) {
			stats->stat[i].scale = FE_SCALE_COUNTER;
			stats->stat[i].uvalue =
				val[9 + i * 2] << 8 | val[9 + i * 2 + 1];
			stats->stat[i].uvalue *= 204 * 8;
		}
	}

	return 0;
}