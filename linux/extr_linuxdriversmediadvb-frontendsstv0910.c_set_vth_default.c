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
struct stv {int* vth; scalar_t__ regoff; } ;

/* Variables and functions */
 scalar_t__ RSTV0910_P2_VTH12 ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,int) ; 

__attribute__((used)) static int set_vth_default(struct stv *state)
{
	state->vth[0] = 0xd7;
	state->vth[1] = 0x85;
	state->vth[2] = 0x58;
	state->vth[3] = 0x3a;
	state->vth[4] = 0x34;
	state->vth[5] = 0x28;
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 0, state->vth[0]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 1, state->vth[1]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 2, state->vth[2]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 3, state->vth[3]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 4, state->vth[4]);
	write_reg(state, RSTV0910_P2_VTH12 + state->regoff + 5, state->vth[5]);
	return 0;
}