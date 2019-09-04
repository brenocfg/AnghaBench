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
struct blkfront_ring_info {TYPE_1__* dev_info; int /*<<< orphan*/  ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_FULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_start_stopped_hw_queues (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void kick_pending_request_queues_locked(struct blkfront_ring_info *rinfo)
{
	if (!RING_FULL(&rinfo->ring))
		blk_mq_start_stopped_hw_queues(rinfo->dev_info->rq, true);
}