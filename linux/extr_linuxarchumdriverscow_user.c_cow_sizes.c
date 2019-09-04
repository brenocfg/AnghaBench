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
typedef  int __u64 ;

/* Variables and functions */
 unsigned long DIV_ROUND (unsigned long,int) ; 
 int ROUND_UP (int,int) ; 

void cow_sizes(int version, __u64 size, int sectorsize, int align,
	       int bitmap_offset, unsigned long *bitmap_len_out,
	       int *data_offset_out)
{
	if (version < 3) {
		*bitmap_len_out = (size + sectorsize - 1) / (8 * sectorsize);

		*data_offset_out = bitmap_offset + *bitmap_len_out;
		*data_offset_out = (*data_offset_out + sectorsize - 1) /
			sectorsize;
		*data_offset_out *= sectorsize;
	}
	else {
		*bitmap_len_out = DIV_ROUND(size, sectorsize);
		*bitmap_len_out = DIV_ROUND(*bitmap_len_out, 8);

		*data_offset_out = bitmap_offset + *bitmap_len_out;
		*data_offset_out = ROUND_UP(*data_offset_out, align);
	}
}