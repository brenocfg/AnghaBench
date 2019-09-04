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
typedef  size_t u8 ;
typedef  int u16 ;
struct dtv_frontend_properties {int isdbt_sb_mode; TYPE_2__* layer; } ;
struct dib8000_state {TYPE_1__** fe; } ;
struct TYPE_4__ {int modulation; int fec; int segment_count; int /*<<< orphan*/  interleaving; } ;
struct TYPE_3__ {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
#define  DQPSK 136 
#define  FEC_1_2 135 
#define  FEC_2_3 134 
#define  FEC_3_4 133 
#define  FEC_5_6 132 
#define  FEC_7_8 131 
#define  QAM_16 130 
#define  QAM_64 129 
#define  QPSK 128 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,size_t) ; 
 size_t fls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 dib8000_set_layer(struct dib8000_state *state, u8 layer_index, u16 max_constellation)
{
	u8  cr, constellation, time_intlv;
	struct dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;

	switch (c->layer[layer_index].modulation) {
	case DQPSK:
			constellation = 0;
			break;
	case  QPSK:
			constellation = 1;
			break;
	case QAM_16:
			constellation = 2;
			break;
	case QAM_64:
	default:
			constellation = 3;
			break;
	}

	switch (c->layer[layer_index].fec) {
	case FEC_1_2:
			cr = 1;
			break;
	case FEC_2_3:
			cr = 2;
			break;
	case FEC_3_4:
			cr = 3;
			break;
	case FEC_5_6:
			cr = 5;
			break;
	case FEC_7_8:
	default:
			cr = 7;
			break;
	}

	time_intlv = fls(c->layer[layer_index].interleaving);
	if (time_intlv > 3 && !(time_intlv == 4 && c->isdbt_sb_mode == 1))
		time_intlv = 0;

	dib8000_write_word(state, 2 + layer_index, (constellation << 10) | ((c->layer[layer_index].segment_count & 0xf) << 6) | (cr << 3) | time_intlv);
	if (c->layer[layer_index].segment_count > 0) {
		switch (max_constellation) {
		case DQPSK:
		case QPSK:
				if (c->layer[layer_index].modulation == QAM_16 || c->layer[layer_index].modulation == QAM_64)
					max_constellation = c->layer[layer_index].modulation;
				break;
		case QAM_16:
				if (c->layer[layer_index].modulation == QAM_64)
					max_constellation = c->layer[layer_index].modulation;
				break;
		}
	}

	return  max_constellation;
}