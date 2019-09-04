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
typedef  unsigned long u16 ;
typedef  unsigned long s16 ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,unsigned long) ; 
 unsigned long BITS_PER_LONG ; 
 int ENOMEM ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_clear (unsigned long*,int /*<<< orphan*/ ,size_t) ; 
 unsigned long bitmap_find_next_zero_area (unsigned long*,size_t,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ bitmap_intersects (unsigned long*,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  bitmap_set (unsigned long*,unsigned long,unsigned long) ; 
 unsigned long* mask ; 

__attribute__((used)) static int l2r_t2b(u16 w, u16 h, u16 a, s16 offset,
		unsigned long *pos, unsigned long slot_bytes,
		unsigned long *map, size_t num_bits, size_t slot_stride)
{
	int i;
	unsigned long index;
	bool area_free = false;
	unsigned long slots_per_band = PAGE_SIZE / slot_bytes;
	unsigned long bit_offset = (offset > 0) ? offset / slot_bytes : 0;
	unsigned long curr_bit = bit_offset;

	/* reset alignment to 1 if we are matching a specific offset */
	/* adjust alignment - 1 to get to the format expected in bitmaps */
	a = (offset > 0) ? 0 : a - 1;

	/* FIXME Return error if slots_per_band > stride */

	while (curr_bit < num_bits) {
		*pos = bitmap_find_next_zero_area(map, num_bits, curr_bit, w,
				a);

		/* skip forward if we are not at right offset */
		if (bit_offset > 0 && (*pos % slots_per_band != bit_offset)) {
			curr_bit = ALIGN(*pos, slots_per_band) + bit_offset;
			continue;
		}

		/* skip forward to next row if we overlap end of row */
		if ((*pos % slot_stride) + w > slot_stride) {
			curr_bit = ALIGN(*pos, slot_stride) + bit_offset;
			continue;
		}

		/* TODO: Handle overlapping 4K boundaries */

		/* break out of look if we will go past end of container */
		if ((*pos + slot_stride * h) > num_bits)
			break;

		/* generate mask that represents out matching pattern */
		bitmap_clear(mask, 0, slot_stride);
		bitmap_set(mask, (*pos % BITS_PER_LONG), w);

		/* assume the area is free until we find an overlap */
		area_free = true;

		/* check subsequent rows to see if complete area is free */
		for (i = 1; i < h; i++) {
			index = *pos / BITS_PER_LONG + i * 8;
			if (bitmap_intersects(&map[index], mask,
				(*pos % BITS_PER_LONG) + w)) {
				area_free = false;
				break;
			}
		}

		if (area_free)
			break;

		/* go forward past this match */
		if (bit_offset > 0)
			curr_bit = ALIGN(*pos, slots_per_band) + bit_offset;
		else
			curr_bit = *pos + a + 1;
	}

	if (area_free) {
		/* set area as in-use. iterate over rows */
		for (i = 0, index = *pos; i < h; i++, index += slot_stride)
			bitmap_set(map, index, w);
	}

	return (area_free) ? 0 : -ENOMEM;
}