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
typedef  scalar_t__ s64 ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ div_s64 (scalar_t__,int) ; 

__attribute__((used)) static inline s64 max2175_round_closest(s64 dividend, s32 divisor)
{
	if ((dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0))
		return div_s64(dividend + divisor / 2, divisor);

	return div_s64(dividend - divisor / 2, divisor);
}