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
struct TYPE_2__ {scalar_t__ type; } ;
struct xb_req_data {scalar_t__ type; int /*<<< orphan*/  body; TYPE_1__ msg; int /*<<< orphan*/  user_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ XS_ERROR ; 
 scalar_t__ XS_TRANSACTION_END ; 
 scalar_t__ XS_TRANSACTION_START ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xs_state_exit_wq ; 
 int /*<<< orphan*/  xs_state_lock ; 
 int /*<<< orphan*/  xs_state_users ; 
 scalar_t__ xs_suspend_active ; 

void xs_request_exit(struct xb_req_data *req)
{
	spin_lock(&xs_state_lock);
	xs_state_users--;
	if ((req->type == XS_TRANSACTION_START && req->msg.type == XS_ERROR) ||
	    (req->type == XS_TRANSACTION_END && !req->user_req &&
	     !WARN_ON_ONCE(req->msg.type == XS_ERROR &&
			   !strcmp(req->body, "ENOENT"))))
		xs_state_users--;
	spin_unlock(&xs_state_lock);

	if (xs_suspend_active && !xs_state_users)
		wake_up(&xs_state_exit_wq);
}