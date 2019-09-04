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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static unsigned LM93_IN_REL_FROM_REG(u8 reg, int upper, int vid)
{
	const long uv_offset = upper ? (((reg >> 4 & 0x0f) + 1) * 12500) :
				(((reg >> 0 & 0x0f) + 1) * -25000);
	const long uv_vid = vid * 1000;
	return (uv_vid + uv_offset + 5000) / 10000;
}