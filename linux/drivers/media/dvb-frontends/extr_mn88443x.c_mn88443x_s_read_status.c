#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct regmap {int dummy; } ;
struct mn88443x_priv {struct regmap* regmap_s; } ;
struct TYPE_16__ {int len; TYPE_7__* stat; } ;
struct TYPE_14__ {int len; TYPE_5__* stat; } ;
struct TYPE_12__ {int len; TYPE_3__* stat; } ;
struct TYPE_10__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_8__ post_bit_count; TYPE_6__ post_bit_error; TYPE_4__ cnr; TYPE_2__ strength; } ;
typedef  int s64 ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_15__ {int uvalue; void* scale; } ;
struct TYPE_13__ {int uvalue; void* scale; } ;
struct TYPE_11__ {int uvalue; void* scale; } ;
struct TYPE_9__ {int uvalue; void* scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGCREAD_S ; 
 int /*<<< orphan*/  BERCNFLG_S ; 
 int BERCNFLG_S_BERVRDY ; 
 int /*<<< orphan*/  BERVRDL_S ; 
 int /*<<< orphan*/  BERVRDU_S ; 
 int /*<<< orphan*/  CNRDXL_S ; 
 int /*<<< orphan*/  CNRDXU_S ; 
 int /*<<< orphan*/  CNRDYL_S ; 
 int /*<<< orphan*/  CNRDYU_S ; 
 int /*<<< orphan*/  CPMON1_S ; 
 int CPMON1_S_FSYNC ; 
 int CPMON1_S_W2LOCK ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* FE_SCALE_RELATIVE ; 
 int abs (int) ; 
 int div_u64 (int,int) ; 
 int intlog10 (int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mn88443x_s_read_status(struct mn88443x_priv *chip,
				  struct dtv_frontend_properties *c,
				  enum fe_status *status)
{
	struct regmap *r_s = chip->regmap_s;
	u32 cpmon, tmpu, tmpl, flg;
	u64 tmp;

	/* Sync detection */
	regmap_read(r_s, CPMON1_S, &cpmon);

	*status = 0;
	if (cpmon & CPMON1_S_FSYNC)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	if (cpmon & CPMON1_S_W2LOCK)
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;

	/* Signal strength */
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	if (*status & FE_HAS_SIGNAL) {
		u32 agc;

		regmap_read(r_s, AGCREAD_S, &tmpu);
		agc = tmpu << 8;

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = agc;
	}

	/* C/N rate */
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	if (*status & FE_HAS_VITERBI) {
		u32 cnr = 0, x, y, d;
		u64 d_3 = 0;

		regmap_read(r_s, CNRDXU_S, &tmpu);
		regmap_read(r_s, CNRDXL_S, &tmpl);
		x = (tmpu << 8) | tmpl;
		regmap_read(r_s, CNRDYU_S, &tmpu);
		regmap_read(r_s, CNRDYL_S, &tmpl);
		y = (tmpu << 8) | tmpl;

		/* CNR[dB]: 10 * log10(D) - 30.74 / D^3 - 3 */
		/*   D = x^2 / (2^15 * y - x^2) */
		d = (y << 15) - x * x;
		if (d > 0) {
			/* (2^4 * D)^3 = 2^12 * D^3 */
			/* 3.074 * 2^(12 + 24) = 211243671486 */
			d_3 = div_u64(16 * x * x, d);
			d_3 = d_3 * d_3 * d_3;
			if (d_3)
				d_3 = div_u64(211243671486ULL, d_3);
		}

		if (d_3) {
			/* 0.3 * 2^24 = 5033164 */
			tmp = (s64)2 * intlog10(x) - intlog10(abs(d)) - d_3
				- 5033164;
			cnr = div_u64(tmp * 10000, 1 << 24);
		}

		if (cnr) {
			c->cnr.len = 1;
			c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			c->cnr.stat[0].uvalue = cnr;
		}
	}

	/* BER */
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	regmap_read(r_s, BERCNFLG_S, &flg);

	if ((*status & FE_HAS_VITERBI) && (flg & BERCNFLG_S_BERVRDY)) {
		u32 bit_err, bit_cnt;

		regmap_read(r_s, BERVRDU_S, &tmpu);
		regmap_read(r_s, BERVRDL_S, &tmpl);
		bit_err = (tmpu << 8) | tmpl;
		bit_cnt = (1 << 13) * 204;

		if (bit_cnt) {
			c->post_bit_error.len = 1;
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = bit_err;
			c->post_bit_count.len = 1;
			c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_count.stat[0].uvalue = bit_cnt;
		}
	}

	return 0;
}