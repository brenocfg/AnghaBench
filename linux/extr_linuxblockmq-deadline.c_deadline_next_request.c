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
struct request {int /*<<< orphan*/  q; } ;
struct deadline_data {int /*<<< orphan*/  zone_lock; struct request** next_rq; } ;

/* Variables and functions */
 int READ ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WRITE ; 
 int /*<<< orphan*/  blk_queue_is_zoned (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_req_can_dispatch_to_zone (struct request*) ; 
 struct request* deadline_latter_request (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct request *
deadline_next_request(struct deadline_data *dd, int data_dir)
{
	struct request *rq;
	unsigned long flags;

	if (WARN_ON_ONCE(data_dir != READ && data_dir != WRITE))
		return NULL;

	rq = dd->next_rq[data_dir];
	if (!rq)
		return NULL;

	if (data_dir == READ || !blk_queue_is_zoned(rq->q))
		return rq;

	/*
	 * Look for a write request that can be dispatched, that is one with
	 * an unlocked target zone.
	 */
	spin_lock_irqsave(&dd->zone_lock, flags);
	while (rq) {
		if (blk_req_can_dispatch_to_zone(rq))
			break;
		rq = deadline_latter_request(rq);
	}
	spin_unlock_irqrestore(&dd->zone_lock, flags);

	return rq;
}