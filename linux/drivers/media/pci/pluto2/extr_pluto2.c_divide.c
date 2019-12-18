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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u32 divide(u32 numerator, u32 denominator)
{
	if (denominator == 0)
		return ~0;

	return DIV_ROUND_CLOSEST(numerator, denominator);
}