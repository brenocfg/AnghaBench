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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct stv {int symbol_rate; } ;
typedef  enum fe_stv0910_mod_cod { ____Placeholder_fe_stv0910_mod_cod } fe_stv0910_mod_cod ;

/* Variables and functions */
 int FE_32APSK_910 ; 
 int FE_QPSK_14 ; 
 int /*<<< orphan*/ * s2car_loop ; 

__attribute__((used)) static u8 get_optim_cloop(struct stv *state,
			  enum fe_stv0910_mod_cod mod_cod, u32 pilots)
{
	int i = 0;

	if (mod_cod >= FE_32APSK_910)
		i = ((int)FE_32APSK_910 - (int)FE_QPSK_14) * 10;
	else if (mod_cod >= FE_QPSK_14)
		i = ((int)mod_cod - (int)FE_QPSK_14) * 10;

	if (state->symbol_rate <= 3000000)
		i += 0;
	else if (state->symbol_rate <=  7000000)
		i += 2;
	else if (state->symbol_rate <= 15000000)
		i += 4;
	else if (state->symbol_rate <= 25000000)
		i += 6;
	else
		i += 8;

	if (!pilots)
		i += 1;

	return s2car_loop[i];
}