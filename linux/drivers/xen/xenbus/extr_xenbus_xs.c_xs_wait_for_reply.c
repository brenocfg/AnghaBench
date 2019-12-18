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
struct xsd_sockmsg {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct xb_req_data {scalar_t__ state; TYPE_1__ msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct xb_req_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* read_reply (struct xb_req_data*) ; 
 scalar_t__ xb_req_state_aborted ; 
 scalar_t__ xb_req_state_queued ; 
 scalar_t__ xb_req_state_wait_reply ; 
 int /*<<< orphan*/  xb_write_mutex ; 
 int /*<<< orphan*/  xs_request_exit (struct xb_req_data*) ; 

__attribute__((used)) static void *xs_wait_for_reply(struct xb_req_data *req, struct xsd_sockmsg *msg)
{
	void *ret;

	ret = read_reply(req);

	xs_request_exit(req);

	msg->type = req->msg.type;
	msg->len = req->msg.len;

	mutex_lock(&xb_write_mutex);
	if (req->state == xb_req_state_queued ||
	    req->state == xb_req_state_wait_reply)
		req->state = xb_req_state_aborted;
	else
		kfree(req);
	mutex_unlock(&xb_write_mutex);

	return ret;
}