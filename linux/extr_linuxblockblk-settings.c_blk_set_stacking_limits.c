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
struct queue_limits {void* max_write_zeroes_sectors; void* max_write_same_sectors; void* max_dev_sectors; void* max_sectors; void* max_segment_size; void* max_hw_sectors; void* max_discard_segments; void* max_segments; } ;

/* Variables and functions */
 void* UINT_MAX ; 
 void* USHRT_MAX ; 
 int /*<<< orphan*/  blk_set_default_limits (struct queue_limits*) ; 

void blk_set_stacking_limits(struct queue_limits *lim)
{
	blk_set_default_limits(lim);

	/* Inherit limits from component devices */
	lim->max_segments = USHRT_MAX;
	lim->max_discard_segments = USHRT_MAX;
	lim->max_hw_sectors = UINT_MAX;
	lim->max_segment_size = UINT_MAX;
	lim->max_sectors = UINT_MAX;
	lim->max_dev_sectors = UINT_MAX;
	lim->max_write_same_sectors = UINT_MAX;
	lim->max_write_zeroes_sectors = UINT_MAX;
}