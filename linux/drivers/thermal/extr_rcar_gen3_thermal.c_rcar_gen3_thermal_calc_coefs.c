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
struct TYPE_2__ {int a1; int b1; int a2; int b2; } ;
struct rcar_gen3_thermal_tsc {int tj_t; TYPE_1__ coef; } ;

/* Variables and functions */
 void* FIXPT_DIV (int,int) ; 
 int FIXPT_INT (int const) ; 
 int TJ_3 ; 

__attribute__((used)) static void rcar_gen3_thermal_calc_coefs(struct rcar_gen3_thermal_tsc *tsc,
					 int *ptat, const int *thcode,
					 int ths_tj_1)
{
	/* TODO: Find documentation and document constant calculation formula */

	/*
	 * Division is not scaled in BSP and if scaled it might overflow
	 * the dividend (4095 * 4095 << 14 > INT_MAX) so keep it unscaled
	 */
	tsc->tj_t = (FIXPT_INT((ptat[1] - ptat[2]) * 157)
		     / (ptat[0] - ptat[2])) + FIXPT_INT(TJ_3);

	tsc->coef.a1 = FIXPT_DIV(FIXPT_INT(thcode[1] - thcode[2]),
				 tsc->tj_t - FIXPT_INT(TJ_3));
	tsc->coef.b1 = FIXPT_INT(thcode[2]) - tsc->coef.a1 * TJ_3;

	tsc->coef.a2 = FIXPT_DIV(FIXPT_INT(thcode[1] - thcode[0]),
				 tsc->tj_t - FIXPT_INT(ths_tj_1));
	tsc->coef.b2 = FIXPT_INT(thcode[0]) - tsc->coef.a2 * ths_tj_1;
}