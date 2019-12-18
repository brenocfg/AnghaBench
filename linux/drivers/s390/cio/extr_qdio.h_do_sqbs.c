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
typedef  unsigned long u64 ;

/* Variables and functions */

__attribute__((used)) static inline int do_sqbs(u64 token, unsigned char state, int queue,
			  int *start, int *count)
{
	register unsigned long _ccq asm ("0") = *count;
	register unsigned long _token asm ("1") = token;
	unsigned long _queuestart = ((unsigned long)queue << 32) | *start;

	asm volatile(
		"	.insn	rsy,0xeb000000008A,%1,0,0(%2)"
		: "+d" (_ccq), "+d" (_queuestart)
		: "d" ((unsigned long)state), "d" (_token)
		: "memory", "cc");
	*count = _ccq & 0xff;
	*start = _queuestart & 0xff;

	return (_ccq >> 32) & 0xff;
}