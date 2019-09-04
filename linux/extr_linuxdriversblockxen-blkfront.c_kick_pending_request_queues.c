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
struct blkfront_ring_info {int /*<<< orphan*/  ring_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kick_pending_request_queues_locked (struct blkfront_ring_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kick_pending_request_queues(struct blkfront_ring_info *rinfo)
{
	unsigned long flags;

	spin_lock_irqsave(&rinfo->ring_lock, flags);
	kick_pending_request_queues_locked(rinfo);
	spin_unlock_irqrestore(&rinfo->ring_lock, flags);
}