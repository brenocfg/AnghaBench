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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ const s32 ;

/* Variables and functions */
 scalar_t__ U32_MAX ; 
 scalar_t__ abs (scalar_t__ const) ; 

const void *
__v4l2_find_nearest_size(const void *array, size_t array_size,
			 size_t entry_size, size_t width_offset,
			 size_t height_offset, s32 width, s32 height)
{
	u32 error, min_error = U32_MAX;
	const void *best = NULL;
	unsigned int i;

	if (!array)
		return NULL;

	for (i = 0; i < array_size; i++, array += entry_size) {
		const u32 *entry_width = array + width_offset;
		const u32 *entry_height = array + height_offset;

		error = abs(*entry_width - width) + abs(*entry_height - height);
		if (error > min_error)
			continue;

		min_error = error;
		best = array;
		if (!error)
			break;
	}

	return best;
}