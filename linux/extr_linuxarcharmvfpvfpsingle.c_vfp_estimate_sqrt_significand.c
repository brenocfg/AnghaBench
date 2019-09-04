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
typedef  int u64 ;
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int* sqrt_evenadjust ; 
 int* sqrt_oddadjust ; 

u32 vfp_estimate_sqrt_significand(u32 exponent, u32 significand)
{
	int index;
	u32 z, a;

	if ((significand & 0xc0000000) != 0x40000000) {
		pr_warn("VFP: estimate_sqrt: invalid significand\n");
	}

	a = significand << 1;
	index = (a >> 27) & 15;
	if (exponent & 1) {
		z = 0x4000 + (a >> 17) - sqrt_oddadjust[index];
		z = ((a / z) << 14) + (z << 15);
		a >>= 1;
	} else {
		z = 0x8000 + (a >> 17) - sqrt_evenadjust[index];
		z = a / z + z;
		z = (z >= 0x20000) ? 0xffff8000 : (z << 15);
		if (z <= a)
			return (s32)a >> 1;
	}
	{
		u64 v = (u64)a << 31;
		do_div(v, z);
		return v + (z >> 1);
	}
}