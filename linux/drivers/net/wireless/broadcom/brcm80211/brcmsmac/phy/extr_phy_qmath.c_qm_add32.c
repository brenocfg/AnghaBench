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
typedef  scalar_t__ s32 ;

/* Variables and functions */

s32 qm_add32(s32 op1, s32 op2)
{
	s32 result;
	result = op1 + op2;
	if (op1 < 0 && op2 < 0 && result > 0)
		result = 0x80000000;
	else if (op1 > 0 && op2 > 0 && result < 0)
		result = 0x7fffffff;

	return result;
}