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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 vfp_hi64to32jamming(u64 val)
{
	u32 v;

	asm(
	"cmp	%Q1, #1		@ vfp_hi64to32jamming\n\t"
	"movcc	%0, %R1\n\t"
	"orrcs	%0, %R1, #1"
	: "=r" (v) : "r" (val) : "cc");

	return v;
}