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

/* Variables and functions */
 unsigned int UDFS_PER_SLICE ; 

__attribute__((used)) static inline unsigned int bcm_sf2_get_num_udf_slices(const u8 *layout)
{
	unsigned int i, count = 0;

	for (i = 0; i < UDFS_PER_SLICE; i++) {
		if (layout[i] != 0)
			count++;
	}

	return count;
}