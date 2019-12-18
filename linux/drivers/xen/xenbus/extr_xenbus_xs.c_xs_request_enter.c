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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ type; } ;
struct xb_req_data {scalar_t__ type; int /*<<< orphan*/  user_req; TYPE_1__ msg; } ;

/* Variables and functions */
 scalar_t__ XS_TRANSACTION_START ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xs_request_id ; 
 int /*<<< orphan*/  xs_state_enter_wq ; 
 int /*<<< orphan*/  xs_state_lock ; 
 int /*<<< orphan*/  xs_state_users ; 
 scalar_t__ xs_suspend_active ; 

__attribute__((used)) static uint32_t xs_request_enter(struct xb_req_data *req)
{
	uint32_t rq_id;

	req->type = req->msg.type;

	spin_lock(&xs_state_lock);

	while (!xs_state_users && xs_suspend_active) {
		spin_unlock(&xs_state_lock);
		wait_event(xs_state_enter_wq, xs_suspend_active == 0);
		spin_lock(&xs_state_lock);
	}

	if (req->type == XS_TRANSACTION_START && !req->user_req)
		xs_state_users++;
	xs_state_users++;
	rq_id = xs_request_id++;

	spin_unlock(&xs_state_lock);

	return rq_id;
}