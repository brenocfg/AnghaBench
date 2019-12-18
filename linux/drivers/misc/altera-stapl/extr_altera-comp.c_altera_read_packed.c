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
 scalar_t__ CHAR_BITS ; 
 scalar_t__ SHORT_BITS ; 

__attribute__((used)) static u32 altera_read_packed(u8 *buffer, u32 bits, u32 *bits_avail,
							u32 *in_index)
{
	u32 result = 0;
	u32 shift = 0;
	u32 databyte = 0;

	while (bits > 0) {
		databyte = buffer[*in_index];
		result |= (((databyte >> (CHAR_BITS - *bits_avail))
			& (0xff >> (CHAR_BITS - *bits_avail))) << shift);

		if (bits <= *bits_avail) {
			result &= (0xffff >> (SHORT_BITS - (bits + shift)));
			*bits_avail -= bits;
			bits = 0;
		} else {
			++(*in_index);
			shift += *bits_avail;
			bits -= *bits_avail;
			*bits_avail = CHAR_BITS;
		}
	}

	return result;
}