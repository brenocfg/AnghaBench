#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct stv {scalar_t__ receive_mode; scalar_t__ regoff; } ;
struct dvb_frontend {struct stv* demodulator_priv; } ;
struct dtv_frontend_properties {int modulation; int fec_inner; size_t symbol_rate; int /*<<< orphan*/  rolloff; int /*<<< orphan*/  pilot; } ;
typedef  enum fe_modulation { ____Placeholder_fe_modulation } fe_modulation ;
typedef  enum fe_code_rate { ____Placeholder_fe_code_rate } fe_code_rate ;

/* Variables and functions */
 int const APSK_16 ; 
 int const APSK_32 ; 
 int const FEC_1_2 ; 
 int const FEC_2_3 ; 
 int const FEC_2_5 ; 
 int const FEC_3_4 ; 
 int const FEC_3_5 ; 
 int const FEC_4_5 ; 
 int const FEC_5_6 ; 
 int FEC_7_8 ; 
 int const FEC_8_9 ; 
 int const FEC_9_10 ; 
 int const FEC_NONE ; 
 int /*<<< orphan*/  PILOT_OFF ; 
 int /*<<< orphan*/  PILOT_ON ; 
 int const PSK_8 ; 
 int const QPSK ; 
 scalar_t__ RCVMODE_DVBS ; 
 scalar_t__ RCVMODE_DVBS2 ; 
 scalar_t__ RCVMODE_NONE ; 
 int /*<<< orphan*/  ROLLOFF_35 ; 
 scalar_t__ RSTV0910_P2_DMDMODCOD ; 
 scalar_t__ RSTV0910_P2_VITCURPUN ; 
 int /*<<< orphan*/  get_cur_symbol_rate (struct stv*,size_t*) ; 
 int /*<<< orphan*/  read_reg (struct stv*,scalar_t__,int*) ; 

__attribute__((used)) static int get_frontend(struct dvb_frontend *fe,
			struct dtv_frontend_properties *p)
{
	struct stv *state = fe->demodulator_priv;
	u8 tmp;
	u32 symbolrate;

	if (state->receive_mode == RCVMODE_DVBS2) {
		u32 mc;
		const enum fe_modulation modcod2mod[0x20] = {
			QPSK, QPSK, QPSK, QPSK,
			QPSK, QPSK, QPSK, QPSK,
			QPSK, QPSK, QPSK, QPSK,
			PSK_8, PSK_8, PSK_8, PSK_8,
			PSK_8, PSK_8, APSK_16, APSK_16,
			APSK_16, APSK_16, APSK_16, APSK_16,
			APSK_32, APSK_32, APSK_32, APSK_32,
			APSK_32,
		};
		const enum fe_code_rate modcod2fec[0x20] = {
			FEC_NONE, FEC_NONE, FEC_NONE, FEC_2_5,
			FEC_1_2, FEC_3_5, FEC_2_3, FEC_3_4,
			FEC_4_5, FEC_5_6, FEC_8_9, FEC_9_10,
			FEC_3_5, FEC_2_3, FEC_3_4, FEC_5_6,
			FEC_8_9, FEC_9_10, FEC_2_3, FEC_3_4,
			FEC_4_5, FEC_5_6, FEC_8_9, FEC_9_10,
			FEC_3_4, FEC_4_5, FEC_5_6, FEC_8_9,
			FEC_9_10
		};
		read_reg(state, RSTV0910_P2_DMDMODCOD + state->regoff, &tmp);
		mc = ((tmp & 0x7c) >> 2);
		p->pilot = (tmp & 0x01) ? PILOT_ON : PILOT_OFF;
		p->modulation = modcod2mod[mc];
		p->fec_inner = modcod2fec[mc];
	} else if (state->receive_mode == RCVMODE_DVBS) {
		read_reg(state, RSTV0910_P2_VITCURPUN + state->regoff, &tmp);
		switch (tmp & 0x1F) {
		case 0x0d:
			p->fec_inner = FEC_1_2;
			break;
		case 0x12:
			p->fec_inner = FEC_2_3;
			break;
		case 0x15:
			p->fec_inner = FEC_3_4;
			break;
		case 0x18:
			p->fec_inner = FEC_5_6;
			break;
		case 0x1a:
			p->fec_inner = FEC_7_8;
			break;
		default:
			p->fec_inner = FEC_NONE;
			break;
		}
		p->rolloff = ROLLOFF_35;
	}

	if (state->receive_mode != RCVMODE_NONE) {
		get_cur_symbol_rate(state, &symbolrate);
		p->symbol_rate = symbolrate;
	}
	return 0;
}