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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */

__attribute__((used)) static inline void sub128(u64 *resh, u64 *resl, u64 nh, u64 nl, u64 mh, u64 ml)
{
	asm(	"subs	%Q0, %Q2, %Q4\n\t"
		"sbcs	%R0, %R2, %R4\n\t"
		"sbcs	%Q1, %Q3, %Q5\n\t"
		"sbc	%R1, %R3, %R5\n\t"
	    : "=r" (nl), "=r" (nh)
	    : "0" (nl), "1" (nh), "r" (ml), "r" (mh)
	    : "cc");
	*resh = nh;
	*resl = nl;
}