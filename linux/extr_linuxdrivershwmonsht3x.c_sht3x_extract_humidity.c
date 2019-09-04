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
typedef  scalar_t__ u16 ;

/* Variables and functions */

__attribute__((used)) static u32 sht3x_extract_humidity(u16 raw)
{
	/*
	 * From datasheet:
	 * RH = 100 * SRH / 2^16
	 * Adapted for integer fixed point (3 digit) arithmetic.
	 */
	return (12500 * (u32)raw) >> 13;
}