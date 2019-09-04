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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int do_div (int,int) ; 

__attribute__((used)) static void
cdv_intel_reduce_ratio(uint32_t *num, uint32_t *den)
{
	/*
	while (*num > 0xffffff || *den > 0xffffff) {
		*num >>= 1;
		*den >>= 1;
	}*/
	uint64_t value, m;
	m = *num;
	value = m * (0x800000);
	m = do_div(value, *den);
	*num = value;
	*den = 0x800000;
}