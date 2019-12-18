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
typedef  long u8 ;
typedef  long u32 ;

/* Variables and functions */

__attribute__((used)) static void altera_concatenate_data(u8 *buffer,
				u8 *preamble_data,
				u32 preamble_count,
				u8 *target_data,
				u32 start_index,
				u32 target_count,
				u8 *postamble_data,
				u32 postamble_count)
/*
 * Copies preamble data, target data, and postamble data
 * into one buffer for IR or DR scans.
 */
{
	u32 i, j, k;

	for (i = 0L; i < preamble_count; ++i) {
		if (preamble_data[i >> 3L] & (1L << (i & 7L)))
			buffer[i >> 3L] |= (1L << (i & 7L));
		else
			buffer[i >> 3L] &= ~(u32)(1L << (i & 7L));

	}

	j = start_index;
	k = preamble_count + target_count;
	for (; i < k; ++i, ++j) {
		if (target_data[j >> 3L] & (1L << (j & 7L)))
			buffer[i >> 3L] |= (1L << (i & 7L));
		else
			buffer[i >> 3L] &= ~(u32)(1L << (i & 7L));

	}

	j = 0L;
	k = preamble_count + target_count + postamble_count;
	for (; i < k; ++i, ++j) {
		if (postamble_data[j >> 3L] & (1L << (j & 7L)))
			buffer[i >> 3L] |= (1L << (i & 7L));
		else
			buffer[i >> 3L] &= ~(u32)(1L << (i & 7L));

	}
}