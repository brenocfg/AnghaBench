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

/* Variables and functions */
 int MT2063_fLO_FractionalTerm (int,int,int) ; 

__attribute__((used)) static u32 MT2063_CalcLO1Mult(u32 *Div,
			      u32 *FracN,
			      u32 f_LO,
			      u32 f_LO_Step, u32 f_Ref)
{
	/*  Calculate the whole number portion of the divider */
	*Div = f_LO / f_Ref;

	/*  Calculate the numerator value (round to nearest f_LO_Step) */
	*FracN =
	    (64 * (((f_LO % f_Ref) + (f_LO_Step / 2)) / f_LO_Step) +
	     (f_Ref / f_LO_Step / 2)) / (f_Ref / f_LO_Step);

	return (f_Ref * (*Div)) + MT2063_fLO_FractionalTerm(f_Ref, *FracN, 64);
}