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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u32 ;

/* Variables and functions */

uint32_t phm_set_field_to_u32(u32 offset, u32 original_data, u32 field, u32 size)
{
	u32 mask = 0;
	u32 shift = 0;

	shift = (offset % 4) << 3;
	if (size == sizeof(uint8_t))
		mask = 0xFF << shift;
	else if (size == sizeof(uint16_t))
		mask = 0xFFFF << shift;

	original_data &= ~mask;
	original_data |= (field << shift);
	return original_data;
}