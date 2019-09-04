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
typedef  int reg_size_t ;

/* Variables and functions */
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  __ocbi (int) ; 
 int register_align (void*) ; 

__attribute__((used)) static void sh4__flush_invalidate_region(void *start, int size)
{
	reg_size_t aligned_start, v, cnt, end;

	aligned_start = register_align(start);
	v = aligned_start & ~(L1_CACHE_BYTES-1);
	end = (aligned_start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);
	cnt = (end - v) / L1_CACHE_BYTES;

	while (cnt >= 8) {
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		cnt -= 8;
	}

	while (cnt) {
		__ocbi(v); v += L1_CACHE_BYTES;
		cnt--;
	}
}