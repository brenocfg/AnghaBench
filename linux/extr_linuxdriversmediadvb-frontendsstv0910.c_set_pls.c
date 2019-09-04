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
typedef  int u32 ;
struct stv {int cur_scrambling_code; scalar_t__ regoff; } ;

/* Variables and functions */
 scalar_t__ RSTV0910_P2_PLROOT0 ; 
 scalar_t__ RSTV0910_P2_PLROOT1 ; 
 scalar_t__ RSTV0910_P2_PLROOT2 ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,int) ; 

__attribute__((used)) static void set_pls(struct stv *state, u32 pls_code)
{
	if (pls_code == state->cur_scrambling_code)
		return;

	/* PLROOT2 bit 2 = gold code */
	write_reg(state, RSTV0910_P2_PLROOT0 + state->regoff,
		  pls_code & 0xff);
	write_reg(state, RSTV0910_P2_PLROOT1 + state->regoff,
		  (pls_code >> 8) & 0xff);
	write_reg(state, RSTV0910_P2_PLROOT2 + state->regoff,
		  0x04 | ((pls_code >> 16) & 0x03));
	state->cur_scrambling_code = pls_code;
}