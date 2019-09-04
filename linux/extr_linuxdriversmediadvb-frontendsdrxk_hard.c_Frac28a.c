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

__attribute__((used)) static inline u32 Frac28a(u32 a, u32 c)
{
	int i = 0;
	u32 Q1 = 0;
	u32 R0 = 0;

	R0 = (a % c) << 4;	/* 32-28 == 4 shifts possible at max */
	Q1 = a / c;		/*
				 * integer part, only the 4 least significant
				 * bits will be visible in the result
				 */

	/* division using radix 16, 7 nibbles in the result */
	for (i = 0; i < 7; i++) {
		Q1 = (Q1 << 4) | (R0 / c);
		R0 = (R0 % c) << 4;
	}
	/* rounding */
	if ((R0 >> 3) >= c)
		Q1++;

	return Q1;
}