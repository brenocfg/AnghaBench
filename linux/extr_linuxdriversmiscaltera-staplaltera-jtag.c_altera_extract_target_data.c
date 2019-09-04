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

__attribute__((used)) static void altera_extract_target_data(u8 *buffer,
				u8 *target_data,
				u32 start_index,
				u32 preamble_count,
				u32 target_count)
/*
 * Copies target data from scan buffer, filtering out
 * preamble and postamble data.
 */
{
	u32 i;
	u32 j;
	u32 k;

	j = preamble_count;
	k = start_index + target_count;
	for (i = start_index; i < k; ++i, ++j) {
		if (buffer[j >> 3] & (1 << (j & 7)))
			target_data[i >> 3] |= (1 << (i & 7));
		else
			target_data[i >> 3] &= ~(u32)(1 << (i & 7));

	}
}