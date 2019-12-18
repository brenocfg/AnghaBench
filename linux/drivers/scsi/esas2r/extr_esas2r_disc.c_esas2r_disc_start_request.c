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
struct esas2r_request {scalar_t__ timeout; int /*<<< orphan*/  req_list; int /*<<< orphan*/  req_type; } ;
struct esas2r_adapter {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  defer_list; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CHPRST_PENDING ; 
 int /*<<< orphan*/  AF_FLASHING ; 
 scalar_t__ ESAS2R_DEFAULT_TMO ; 
 int /*<<< orphan*/  RT_DISC_REQ ; 
 int /*<<< orphan*/  esas2r_disc_local_start_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool esas2r_disc_start_request(struct esas2r_adapter *a,
				      struct esas2r_request *rq)
{
	unsigned long flags;

	/* Set the timeout to a minimum value. */
	if (rq->timeout < ESAS2R_DEFAULT_TMO)
		rq->timeout = ESAS2R_DEFAULT_TMO;

	/*
	 * Override the request type to distinguish discovery requests.  If we
	 * end up deferring the request, esas2r_disc_local_start_request()
	 * will be called to restart it.
	 */
	rq->req_type = RT_DISC_REQ;

	spin_lock_irqsave(&a->queue_lock, flags);

	if (!test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    !test_bit(AF_FLASHING, &a->flags))
		esas2r_disc_local_start_request(a, rq);
	else
		list_add_tail(&rq->req_list, &a->defer_list);

	spin_unlock_irqrestore(&a->queue_lock, flags);

	return true;
}