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
struct dtv_frontend_properties {int isdbt_sb_mode; int transmission_mode; TYPE_2__* layer; int /*<<< orphan*/  isdbt_partial_reception; } ;
struct dib8000_state {int const seg_diff_mask; int const seg_mask; TYPE_1__** fe; } ;
typedef  int s16 ;
struct TYPE_4__ {int /*<<< orphan*/  modulation; } ;
struct TYPE_3__ {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQPSK ; 
#define  TRANSMISSION_MODE_2K 131 
#define  TRANSMISSION_MODE_4K 130 
#define  TRANSMISSION_MODE_8K 129 
#define  TRANSMISSION_MODE_AUTO 128 
 int* coeff_2k_sb_1seg ; 
 int* coeff_2k_sb_1seg_dqpsk ; 
 int* coeff_2k_sb_3seg ; 
 int* coeff_2k_sb_3seg_0dqpsk ; 
 int* coeff_2k_sb_3seg_0dqpsk_1dqpsk ; 
 int* coeff_2k_sb_3seg_1dqpsk ; 
 int* coeff_4k_sb_1seg ; 
 int* coeff_4k_sb_1seg_dqpsk ; 
 int* coeff_4k_sb_3seg ; 
 int* coeff_4k_sb_3seg_0dqpsk ; 
 int* coeff_4k_sb_3seg_0dqpsk_1dqpsk ; 
 int* coeff_4k_sb_3seg_1dqpsk ; 
 int* coeff_8k_sb_1seg ; 
 int* coeff_8k_sb_1seg_dqpsk ; 
 int* coeff_8k_sb_3seg ; 
 int* coeff_8k_sb_3seg_0dqpsk ; 
 int* coeff_8k_sb_3seg_0dqpsk_1dqpsk ; 
 int* coeff_8k_sb_3seg_1dqpsk ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int const) ; 

__attribute__((used)) static void dib8000_small_fine_tune(struct dib8000_state *state)
{
	u16 i;
	const s16 *ncoeff;
	struct dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;

	dib8000_write_word(state, 352, state->seg_diff_mask);
	dib8000_write_word(state, 353, state->seg_mask);

	/* P_small_coef_ext_enable=ISDB-Tsb, P_small_narrow_band=ISDB-Tsb, P_small_last_seg=13, P_small_offset_num_car=5 */
	dib8000_write_word(state, 351, (c->isdbt_sb_mode << 9) | (c->isdbt_sb_mode << 8) | (13 << 4) | 5);

	if (c->isdbt_sb_mode) {
		/* ---- SMALL ---- */
		switch (c->transmission_mode) {
		case TRANSMISSION_MODE_2K:
				if (c->isdbt_partial_reception == 0) { /* 1-seg */
					if (c->layer[0].modulation == DQPSK) /* DQPSK */
						ncoeff = coeff_2k_sb_1seg_dqpsk;
					else /* QPSK or QAM */
						ncoeff = coeff_2k_sb_1seg;
				} else { /* 3-segments */
					if (c->layer[0].modulation == DQPSK) { /* DQPSK on central segment */
						if (c->layer[1].modulation == DQPSK) /* DQPSK on external segments */
							ncoeff = coeff_2k_sb_3seg_0dqpsk_1dqpsk;
						else /* QPSK or QAM on external segments */
							ncoeff = coeff_2k_sb_3seg_0dqpsk;
					} else { /* QPSK or QAM on central segment */
						if (c->layer[1].modulation == DQPSK) /* DQPSK on external segments */
							ncoeff = coeff_2k_sb_3seg_1dqpsk;
						else /* QPSK or QAM on external segments */
							ncoeff = coeff_2k_sb_3seg;
					}
				}
				break;
		case TRANSMISSION_MODE_4K:
				if (c->isdbt_partial_reception == 0) { /* 1-seg */
					if (c->layer[0].modulation == DQPSK) /* DQPSK */
						ncoeff = coeff_4k_sb_1seg_dqpsk;
					else /* QPSK or QAM */
						ncoeff = coeff_4k_sb_1seg;
				} else { /* 3-segments */
					if (c->layer[0].modulation == DQPSK) { /* DQPSK on central segment */
						if (c->layer[1].modulation == DQPSK) /* DQPSK on external segments */
							ncoeff = coeff_4k_sb_3seg_0dqpsk_1dqpsk;
						else /* QPSK or QAM on external segments */
							ncoeff = coeff_4k_sb_3seg_0dqpsk;
					} else { /* QPSK or QAM on central segment */
						if (c->layer[1].modulation == DQPSK) /* DQPSK on external segments */
							ncoeff = coeff_4k_sb_3seg_1dqpsk;
						else /* QPSK or QAM on external segments */
							ncoeff = coeff_4k_sb_3seg;
					}
				}
				break;
		case TRANSMISSION_MODE_AUTO:
		case TRANSMISSION_MODE_8K:
		default:
				if (c->isdbt_partial_reception == 0) { /* 1-seg */
					if (c->layer[0].modulation == DQPSK) /* DQPSK */
						ncoeff = coeff_8k_sb_1seg_dqpsk;
					else /* QPSK or QAM */
						ncoeff = coeff_8k_sb_1seg;
				} else { /* 3-segments */
					if (c->layer[0].modulation == DQPSK) { /* DQPSK on central segment */
						if (c->layer[1].modulation == DQPSK) /* DQPSK on external segments */
							ncoeff = coeff_8k_sb_3seg_0dqpsk_1dqpsk;
						else /* QPSK or QAM on external segments */
							ncoeff = coeff_8k_sb_3seg_0dqpsk;
					} else { /* QPSK or QAM on central segment */
						if (c->layer[1].modulation == DQPSK) /* DQPSK on external segments */
							ncoeff = coeff_8k_sb_3seg_1dqpsk;
						else /* QPSK or QAM on external segments */
							ncoeff = coeff_8k_sb_3seg;
					}
				}
				break;
		}

		for (i = 0; i < 8; i++)
			dib8000_write_word(state, 343 + i, ncoeff[i]);
	}
}