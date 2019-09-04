#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sigh; scalar_t__ sigl; } ;
typedef  TYPE_1__ FPU_REG ;

/* Variables and functions */
 int EXP_BIAS ; 
 int EXP_OVER ; 
 int EXP_UNDER ; 
 int TW_Denormal ; 
 int TW_Infinity ; 
 int TW_NaN ; 
 int exponent (TYPE_1__ const*) ; 

int FPU_Special(FPU_REG const *ptr)
{
	int exp = exponent(ptr);

	if (exp == EXP_BIAS + EXP_UNDER)
		return TW_Denormal;
	else if (exp != EXP_BIAS + EXP_OVER)
		return TW_NaN;
	else if ((ptr->sigh == 0x80000000) && (ptr->sigl == 0))
		return TW_Infinity;
	return TW_NaN;
}