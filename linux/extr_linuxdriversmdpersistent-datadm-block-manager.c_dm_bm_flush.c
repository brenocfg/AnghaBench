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
struct dm_block_manager {int /*<<< orphan*/  bufio; scalar_t__ read_only; } ;

/* Variables and functions */
 int EPERM ; 
 int dm_bufio_write_dirty_buffers (int /*<<< orphan*/ ) ; 

int dm_bm_flush(struct dm_block_manager *bm)
{
	if (bm->read_only)
		return -EPERM;

	return dm_bufio_write_dirty_buffers(bm->bufio);
}