#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct stv {TYPE_1__* base; scalar_t__ regoff; int /*<<< orphan*/  started; } ;
typedef  int s64 ;
typedef  int s32 ;
struct TYPE_2__ {int mclk; } ;

/* Variables and functions */
 scalar_t__ RSTV0910_P2_SFR0 ; 
 scalar_t__ RSTV0910_P2_SFR1 ; 
 scalar_t__ RSTV0910_P2_SFR2 ; 
 scalar_t__ RSTV0910_P2_SFR3 ; 
 scalar_t__ RSTV0910_P2_TMGREG0 ; 
 scalar_t__ RSTV0910_P2_TMGREG1 ; 
 scalar_t__ RSTV0910_P2_TMGREG2 ; 
 int /*<<< orphan*/  read_reg (struct stv*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int get_cur_symbol_rate(struct stv *state, u32 *p_symbol_rate)
{
	int status = 0;
	u8 symb_freq0;
	u8 symb_freq1;
	u8 symb_freq2;
	u8 symb_freq3;
	u8 tim_offs0;
	u8 tim_offs1;
	u8 tim_offs2;
	u32 symbol_rate;
	s32 timing_offset;

	*p_symbol_rate = 0;
	if (!state->started)
		return status;

	read_reg(state, RSTV0910_P2_SFR3 + state->regoff, &symb_freq3);
	read_reg(state, RSTV0910_P2_SFR2 + state->regoff, &symb_freq2);
	read_reg(state, RSTV0910_P2_SFR1 + state->regoff, &symb_freq1);
	read_reg(state, RSTV0910_P2_SFR0 + state->regoff, &symb_freq0);
	read_reg(state, RSTV0910_P2_TMGREG2 + state->regoff, &tim_offs2);
	read_reg(state, RSTV0910_P2_TMGREG1 + state->regoff, &tim_offs1);
	read_reg(state, RSTV0910_P2_TMGREG0 + state->regoff, &tim_offs0);

	symbol_rate = ((u32)symb_freq3 << 24) | ((u32)symb_freq2 << 16) |
		((u32)symb_freq1 << 8) | (u32)symb_freq0;
	timing_offset = ((u32)tim_offs2 << 16) | ((u32)tim_offs1 << 8) |
		(u32)tim_offs0;

	if ((timing_offset & (1 << 23)) != 0)
		timing_offset |= 0xFF000000; /* Sign extent */

	symbol_rate = (u32)(((u64)symbol_rate * state->base->mclk) >> 32);
	timing_offset = (s32)(((s64)symbol_rate * (s64)timing_offset) >> 29);

	*p_symbol_rate = symbol_rate + timing_offset;

	return 0;
}