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
struct request {struct dm_rq_target_io* end_io_data; } ;
struct dm_rq_target_io {int /*<<< orphan*/  orig; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  dm_complete_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_clone_request(struct request *clone, blk_status_t error)
{
	struct dm_rq_target_io *tio = clone->end_io_data;

	/*
	 * Actual request completion is done in a softirq context which doesn't
	 * hold the clone's queue lock.  Otherwise, deadlock could occur because:
	 *     - another request may be submitted by the upper level driver
	 *       of the stacking during the completion
	 *     - the submission which requires queue lock may be done
	 *       against this clone's queue
	 */
	dm_complete_request(tio->orig, error);
}