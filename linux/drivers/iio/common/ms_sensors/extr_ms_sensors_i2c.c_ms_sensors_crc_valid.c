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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static bool ms_sensors_crc_valid(u32 value)
{
	u32 polynom = 0x988000;	/* x^8 + x^5 + x^4 + 1 */
	u32 msb = 0x800000;
	u32 mask = 0xFF8000;
	u32 result = value & 0xFFFF00;
	u8 crc = value & 0xFF;

	while (msb != 0x80) {
		if (result & msb)
			result = ((result ^ polynom) & mask)
				| (result & ~mask);
		msb >>= 1;
		mask >>= 1;
		polynom >>= 1;
	}

	return result == crc;
}