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
struct msb_data {int zone_count; int block_count; int read_only; int /*<<< orphan*/  used_blocks_bitmap; scalar_t__* free_block_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int msb_validate_used_block_bitmap(struct msb_data *msb)
{
	int total_free_blocks = 0;
	int i;

	if (!debug)
		return 0;

	for (i = 0; i < msb->zone_count; i++)
		total_free_blocks += msb->free_block_count[i];

	if (msb->block_count - bitmap_weight(msb->used_blocks_bitmap,
					msb->block_count) == total_free_blocks)
		return 0;

	pr_err("BUG: free block counts don't match the bitmap");
	msb->read_only = true;
	return -EINVAL;
}