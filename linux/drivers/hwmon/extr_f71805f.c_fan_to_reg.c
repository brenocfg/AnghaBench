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

__attribute__((used)) static inline u16 fan_to_reg(long rpm)
{
	/*
	 * If the low limit is set below what the chip can measure,
	 * store the largest possible 12-bit value in the registers,
	 * so that no alarm will ever trigger.
	 */
	if (rpm < 367)
		return 0xfff;
	return 1500000 / rpm;
}