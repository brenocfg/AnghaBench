#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct parahotplug_request {int /*<<< orphan*/  list; } ;
struct TYPE_6__ {scalar_t__ active; } ;
struct TYPE_4__ {TYPE_3__ state; } ;
struct TYPE_5__ {TYPE_1__ device_change_state; } ;
struct controlvm_message {TYPE_2__ cmd; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int CONTROLVM_RESP_SUCCESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  controlvm_respond (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct parahotplug_request* parahotplug_request_create (struct controlvm_message*) ; 
 int /*<<< orphan*/  parahotplug_request_destroy (struct parahotplug_request*) ; 
 int parahotplug_request_kickoff (struct parahotplug_request*) ; 
 int /*<<< orphan*/  parahotplug_request_list ; 
 int /*<<< orphan*/  parahotplug_request_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parahotplug_process_message(struct controlvm_message *inmsg)
{
	struct parahotplug_request *req;
	int err;

	req = parahotplug_request_create(inmsg);
	if (!req)
		return -ENOMEM;
	/*
	 * For enable messages, just respond with success right away, we don't
	 * need to wait to see if the enable was successful.
	 */
	if (inmsg->cmd.device_change_state.state.active) {
		err = parahotplug_request_kickoff(req);
		if (err)
			goto err_respond;
		controlvm_respond(&inmsg->hdr, CONTROLVM_RESP_SUCCESS,
				  &inmsg->cmd.device_change_state.state);
		parahotplug_request_destroy(req);
		return 0;
	}
	/*
	 * For disable messages, add the request to the request list before
	 * kicking off the udev script. It won't get responded to until the
	 * script has indicated it's done.
	 */
	spin_lock(&parahotplug_request_list_lock);
	list_add_tail(&req->list, &parahotplug_request_list);
	spin_unlock(&parahotplug_request_list_lock);
	err = parahotplug_request_kickoff(req);
	if (err)
		goto err_respond;
	return 0;

err_respond:
	controlvm_respond(&inmsg->hdr, err,
			  &inmsg->cmd.device_change_state.state);
	return err;
}