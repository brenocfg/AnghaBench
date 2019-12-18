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
struct nvme_ns {int /*<<< orphan*/  disk; int /*<<< orphan*/  queue; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_NS_DEAD ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_set_queue_dying (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_disk (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_set_queue_dying(struct nvme_ns *ns)
{
	/*
	 * Revalidating a dead namespace sets capacity to 0. This will end
	 * buffered writers dirtying pages that can't be synced.
	 */
	if (!ns->disk || test_and_set_bit(NVME_NS_DEAD, &ns->flags))
		return;
	blk_set_queue_dying(ns->queue);
	/* Forcibly unquiesce queues to avoid blocking dispatch */
	blk_mq_unquiesce_queue(ns->queue);
	/*
	 * Revalidate after unblocking dispatchers that may be holding bd_butex
	 */
	revalidate_disk(ns->disk);
}