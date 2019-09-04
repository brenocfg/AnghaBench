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
struct drbd_request {int rq_state; int /*<<< orphan*/  kref; int /*<<< orphan*/  completion_ref; struct drbd_device* device; } ;
struct drbd_device {int dummy; } ;
struct bio_and_error {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int RQ_LOCAL_ABORTED ; 
 int RQ_POSTPONED ; 
 int /*<<< orphan*/  atomic_sub_and_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_req_complete (struct drbd_request*,struct bio_and_error*) ; 
 int /*<<< orphan*/  drbd_req_destroy ; 
 int /*<<< orphan*/  drbd_restart_request (struct drbd_request*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drbd_req_put_completion_ref(struct drbd_request *req, struct bio_and_error *m, int put)
{
	struct drbd_device *device = req->device;
	D_ASSERT(device, m || (req->rq_state & RQ_POSTPONED));

	if (!put)
		return;

	if (!atomic_sub_and_test(put, &req->completion_ref))
		return;

	drbd_req_complete(req, m);

	/* local completion may still come in later,
	 * we need to keep the req object around. */
	if (req->rq_state & RQ_LOCAL_ABORTED)
		return;

	if (req->rq_state & RQ_POSTPONED) {
		/* don't destroy the req object just yet,
		 * but queue it for retry */
		drbd_restart_request(req);
		return;
	}

	kref_put(&req->kref, drbd_req_destroy);
}