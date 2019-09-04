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
struct mapped_device {int /*<<< orphan*/  queue; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_queue_flush (struct mapped_device*) ; 
 scalar_t__ dm_request_based (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_start_queue (int /*<<< orphan*/ ) ; 
 int dm_table_resume_targets (struct dm_table*) ; 
 int /*<<< orphan*/  unlock_fs (struct mapped_device*) ; 

__attribute__((used)) static int __dm_resume(struct mapped_device *md, struct dm_table *map)
{
	if (map) {
		int r = dm_table_resume_targets(map);
		if (r)
			return r;
	}

	dm_queue_flush(md);

	/*
	 * Flushing deferred I/Os must be done after targets are resumed
	 * so that mapping of targets can work correctly.
	 * Request-based dm is queueing the deferred I/Os in its request_queue.
	 */
	if (dm_request_based(md))
		dm_start_queue(md->queue);

	unlock_fs(md);

	return 0;
}