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
typedef  int u64 ;
struct TYPE_2__ {int* stfle_fac_list; int stfl_fac_list; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 TYPE_1__ S390_lowcore ; 
 int* als ; 
 int /*<<< orphan*/  facility_mismatch () ; 

void verify_facilities(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(S390_lowcore.stfle_fac_list); i++)
		S390_lowcore.stfle_fac_list[i] = 0;
	asm volatile(
		"	stfl	0(0)\n"
		: "=m" (S390_lowcore.stfl_fac_list));
	S390_lowcore.stfle_fac_list[0] = (u64)S390_lowcore.stfl_fac_list << 32;
	if (S390_lowcore.stfl_fac_list & 0x01000000) {
		register unsigned long reg0 asm("0") = ARRAY_SIZE(als) - 1;

		asm volatile(".insn s,0xb2b00000,0(%1)" /* stfle */
			     : "+d" (reg0)
			     : "a" (&S390_lowcore.stfle_fac_list)
			     : "memory", "cc");
	}
	for (i = 0; i < ARRAY_SIZE(als); i++) {
		if ((S390_lowcore.stfle_fac_list[i] & als[i]) != als[i])
			facility_mismatch();
	}
}