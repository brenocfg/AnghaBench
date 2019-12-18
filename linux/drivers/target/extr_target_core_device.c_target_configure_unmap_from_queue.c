#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct se_dev_attrib {int max_unmap_lba_count; int max_unmap_block_desc_count; int unmap_granularity; int unmap_granularity_alignment; int /*<<< orphan*/  unmap_zeroes_data; } ;
struct TYPE_2__ {int max_discard_sectors; int discard_granularity; int discard_alignment; int /*<<< orphan*/  max_write_zeroes_sectors; } ;
struct request_queue {TYPE_1__ limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_discard (struct request_queue*) ; 
 int ilog2 (int) ; 
 int queue_logical_block_size (struct request_queue*) ; 

bool target_configure_unmap_from_queue(struct se_dev_attrib *attrib,
				       struct request_queue *q)
{
	int block_size = queue_logical_block_size(q);

	if (!blk_queue_discard(q))
		return false;

	attrib->max_unmap_lba_count =
		q->limits.max_discard_sectors >> (ilog2(block_size) - 9);
	/*
	 * Currently hardcoded to 1 in Linux/SCSI code..
	 */
	attrib->max_unmap_block_desc_count = 1;
	attrib->unmap_granularity = q->limits.discard_granularity / block_size;
	attrib->unmap_granularity_alignment = q->limits.discard_alignment /
								block_size;
	attrib->unmap_zeroes_data = (q->limits.max_write_zeroes_sectors);
	return true;
}