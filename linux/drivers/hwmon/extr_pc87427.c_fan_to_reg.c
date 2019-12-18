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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline u16 fan_to_reg(unsigned long val)
{
	if (val < 83UL)
		return 0xffff;
	if (val >= 1350000UL)
		return 0x0004;
	return ((1350000UL + val / 2) / val) << 2;
}