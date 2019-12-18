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
struct mn88443x_priv {struct regmap* regmap_t; } ;
struct TYPE_16__ {int len; TYPE_7__* stat; } ;
struct TYPE_14__ {int len; TYPE_5__* stat; } ;
struct TYPE_12__ {int len; TYPE_3__* stat; } ;
struct TYPE_10__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_8__ post_bit_count; TYPE_6__ post_bit_error; TYPE_4__ cnr; TYPE_2__ strength; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_15__ {int uvalue; void* scale; } ;
struct TYPE_13__ {int uvalue; void* scale; } ;
struct TYPE_11__ {int uvalue; void* scale; } ;
struct TYPE_9__ {int uvalue; void* scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGCRDL_T ; 
 int /*<<< orphan*/  AGCRDU_T ; 
 int /*<<< orphan*/  BERFLG_T ; 
 int BERFLG_T_BERVRDYA ; 
 int /*<<< orphan*/  BERLENRDL_T ; 
 int /*<<< orphan*/  BERLENRDU_T ; 
 int /*<<< orphan*/  BERRDL_T ; 
 int /*<<< orphan*/  BERRDM_T ; 
 int /*<<< orphan*/  BERRDU_T ; 
 int /*<<< orphan*/  CNRDL_T ; 
 int /*<<< orphan*/  CNRDU_T ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* FE_SCALE_RELATIVE ; 
 int /*<<< orphan*/  SSEQRD_T ; 
 int SSEQRD_T_SSEQSTRD_FRAME_SYNC ; 
 int SSEQRD_T_SSEQSTRD_MASK ; 
 int SSEQRD_T_SSEQSTRD_SYNC ; 
 int div_u64 (int,int) ; 
 int intlog10 (int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mn88443x_t_read_status(struct mn88443x_priv *chip,
				  struct dtv_frontend_properties *c,
				  enum fe_status *status)
{
	struct regmap *r_t = chip->regmap_t;
	u32 seqrd, st, flg, tmpu, tmpm, tmpl;
	u64 tmp;

	/* Sync detection */
	regmap_read(r_t, SSEQRD_T, &seqrd);
	st = seqrd & SSEQRD_T_SSEQSTRD_MASK;

	*status = 0;
	if (st >= SSEQRD_T_SSEQSTRD_SYNC)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	if (st >= SSEQRD_T_SSEQSTRD_FRAME_SYNC)
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;

	/* Signal strength */
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	if (*status & FE_HAS_SIGNAL) {
		u32 agc;

		regmap_read(r_t, AGCRDU_T, &tmpu);
		regmap_read(r_t, AGCRDL_T, &tmpl);
		agc = (tmpu << 8) | tmpl;

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = agc;
	}

	/* C/N rate */
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	if (*status & FE_HAS_VITERBI) {
		u32 cnr;

		regmap_read(r_t, CNRDU_T, &tmpu);
		regmap_read(r_t, CNRDL_T, &tmpl);

		if (tmpu || tmpl) {
			/* CNR[dB]: 10 * (log10(65536 / value) + 0.2) */
			/* intlog10(65536) = 80807124, 0.2 * 2^24 = 3355443 */
			tmp = (u64)80807124 - intlog10((tmpu << 8) | tmpl)
				+ 3355443;
			cnr = div_u64(tmp * 10000, 1 << 24);
		} else {
			cnr = 0;
		}

		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].uvalue = cnr;
	}

	/* BER */
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	regmap_read(r_t, BERFLG_T, &flg);

	if ((*status & FE_HAS_VITERBI) && (flg & BERFLG_T_BERVRDYA)) {
		u32 bit_err, bit_cnt;

		regmap_read(r_t, BERRDU_T, &tmpu);
		regmap_read(r_t, BERRDM_T, &tmpm);
		regmap_read(r_t, BERRDL_T, &tmpl);
		bit_err = (tmpu << 16) | (tmpm << 8) | tmpl;

		regmap_read(r_t, BERLENRDU_T, &tmpu);
		regmap_read(r_t, BERLENRDL_T, &tmpl);
		bit_cnt = ((tmpu << 8) | tmpl) * 203 * 8;

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