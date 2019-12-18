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
struct stv {scalar_t__ receive_mode; int mod_cod; int pilots; int fectype; int is_standard_broadcast; int /*<<< orphan*/  feroll_off; scalar_t__ is_vcm; int /*<<< orphan*/  puncture_rate; scalar_t__ regoff; int /*<<< orphan*/  started; } ;
typedef  enum fe_stv0910_mod_cod { ____Placeholder_fe_stv0910_mod_cod } fe_stv0910_mod_cod ;
typedef  enum dvbs2_fectype { ____Placeholder_dvbs2_fectype } dvbs2_fectype ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FEC_1_2 ; 
 int /*<<< orphan*/  FEC_2_3 ; 
 int /*<<< orphan*/  FEC_3_4 ; 
 int /*<<< orphan*/  FEC_5_6 ; 
 int /*<<< orphan*/  FEC_7_8 ; 
 int /*<<< orphan*/  FEC_NONE ; 
 int /*<<< orphan*/  FE_SAT_35 ; 
 scalar_t__ RCVMODE_DVBS ; 
 scalar_t__ RCVMODE_DVBS2 ; 
 scalar_t__ RSTV0910_P2_DMDMODCOD ; 
 scalar_t__ RSTV0910_P2_VITCURPUN ; 
 int /*<<< orphan*/  read_reg (struct stv*,scalar_t__,int*) ; 

__attribute__((used)) static int get_signal_parameters(struct stv *state)
{
	u8 tmp;

	if (!state->started)
		return -EINVAL;

	if (state->receive_mode == RCVMODE_DVBS2) {
		read_reg(state, RSTV0910_P2_DMDMODCOD + state->regoff, &tmp);
		state->mod_cod = (enum fe_stv0910_mod_cod)((tmp & 0x7c) >> 2);
		state->pilots = (tmp & 0x01) != 0;
		state->fectype = (enum dvbs2_fectype)((tmp & 0x02) >> 1);

	} else if (state->receive_mode == RCVMODE_DVBS) {
		read_reg(state, RSTV0910_P2_VITCURPUN + state->regoff, &tmp);
		state->puncture_rate = FEC_NONE;
		switch (tmp & 0x1F) {
		case 0x0d:
			state->puncture_rate = FEC_1_2;
			break;
		case 0x12:
			state->puncture_rate = FEC_2_3;
			break;
		case 0x15:
			state->puncture_rate = FEC_3_4;
			break;
		case 0x18:
			state->puncture_rate = FEC_5_6;
			break;
		case 0x1a:
			state->puncture_rate = FEC_7_8;
			break;
		}
		state->is_vcm = 0;
		state->is_standard_broadcast = 1;
		state->feroll_off = FE_SAT_35;
	}
	return 0;
}