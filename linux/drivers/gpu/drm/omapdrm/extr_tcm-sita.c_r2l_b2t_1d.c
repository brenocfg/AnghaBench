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
typedef  size_t u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  bitmap_set (unsigned long*,unsigned long,size_t) ; 
 unsigned long find_next_bit (unsigned long*,size_t,unsigned long) ; 

__attribute__((used)) static int r2l_b2t_1d(u16 w, unsigned long *pos, unsigned long *map,
		size_t num_bits)
{
	unsigned long search_count = 0;
	unsigned long bit;
	bool area_found = false;

	*pos = num_bits - w;

	while (search_count < num_bits) {
		bit = find_next_bit(map, num_bits, *pos);

		if (bit - *pos >= w) {
			/* found a long enough free area */
			bitmap_set(map, *pos, w);
			area_found = true;
			break;
		}

		search_count = num_bits - bit + w;
		*pos = bit - w;
	}

	return (area_found) ? 0 : -ENOMEM;
}