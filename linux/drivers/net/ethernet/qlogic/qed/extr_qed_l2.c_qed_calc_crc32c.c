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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ CRC32_POLY ; 

__attribute__((used)) static u32 qed_calc_crc32c(u8 *crc32_packet,
			   u32 crc32_length, u32 crc32_seed, u8 complement)
{
	u32 byte = 0, bit = 0, crc32_result = crc32_seed;
	u8 msb = 0, current_byte = 0;

	if ((!crc32_packet) ||
	    (crc32_length == 0) ||
	    ((crc32_length % 8) != 0))
		return crc32_result;
	for (byte = 0; byte < crc32_length; byte++) {
		current_byte = crc32_packet[byte];
		for (bit = 0; bit < 8; bit++) {
			msb = (u8)(crc32_result >> 31);
			crc32_result = crc32_result << 1;
			if (msb != (0x1 & (current_byte >> bit))) {
				crc32_result = crc32_result ^ CRC32_POLY;
				crc32_result |= 1; /*crc32_result[0] = 1;*/
			}
		}
	}
	return crc32_result;
}