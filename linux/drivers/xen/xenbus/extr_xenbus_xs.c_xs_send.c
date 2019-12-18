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
struct xsd_sockmsg {int /*<<< orphan*/  req_id; } ;
struct xb_req_data {int /*<<< orphan*/  list; struct xsd_sockmsg msg; int /*<<< orphan*/  caller_req_id; int /*<<< orphan*/  wq; int /*<<< orphan*/  state; scalar_t__ err; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xb_req_state_queued ; 
 int /*<<< orphan*/  xb_waitq ; 
 int /*<<< orphan*/  xb_write_list ; 
 int /*<<< orphan*/  xb_write_mutex ; 
 int /*<<< orphan*/  xs_request_enter (struct xb_req_data*) ; 

__attribute__((used)) static void xs_send(struct xb_req_data *req, struct xsd_sockmsg *msg)
{
	bool notify;

	req->msg = *msg;
	req->err = 0;
	req->state = xb_req_state_queued;
	init_waitqueue_head(&req->wq);

	/* Save the caller req_id and restore it later in the reply */
	req->caller_req_id = req->msg.req_id;
	req->msg.req_id = xs_request_enter(req);

	mutex_lock(&xb_write_mutex);
	list_add_tail(&req->list, &xb_write_list);
	notify = list_is_singular(&xb_write_list);
	mutex_unlock(&xb_write_mutex);

	if (notify)
		wake_up(&xb_waitq);
}