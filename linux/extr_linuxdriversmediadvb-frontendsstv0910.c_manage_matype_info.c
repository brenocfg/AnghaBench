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
struct stv {scalar_t__ receive_mode; int feroll_off; int is_vcm; int is_standard_broadcast; scalar_t__ regoff; int /*<<< orphan*/  started; } ;
typedef  enum fe_stv0910_roll_off { ____Placeholder_fe_stv0910_roll_off } fe_stv0910_roll_off ;

/* Variables and functions */
 int EINVAL ; 
 int FE_SAT_35 ; 
 scalar_t__ RCVMODE_DVBS ; 
 scalar_t__ RCVMODE_DVBS2 ; 
 scalar_t__ RSTV0910_P2_MATSTR1 ; 
 int /*<<< orphan*/  read_regs (struct stv*,scalar_t__,int*,int) ; 

__attribute__((used)) static int manage_matype_info(struct stv *state)
{
	if (!state->started)
		return -EINVAL;
	if (state->receive_mode == RCVMODE_DVBS2) {
		u8 bbheader[2];

		read_regs(state, RSTV0910_P2_MATSTR1 + state->regoff,
			  bbheader, 2);
		state->feroll_off =
			(enum fe_stv0910_roll_off)(bbheader[0] & 0x03);
		state->is_vcm = (bbheader[0] & 0x10) == 0;
		state->is_standard_broadcast = (bbheader[0] & 0xFC) == 0xF0;
	} else if (state->receive_mode == RCVMODE_DVBS) {
		state->is_vcm = 0;
		state->is_standard_broadcast = 1;
		state->feroll_off = FE_SAT_35;
	}
	return 0;
}