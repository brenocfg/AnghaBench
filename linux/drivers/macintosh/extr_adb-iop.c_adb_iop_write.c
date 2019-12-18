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
struct adb_request {int nbytes; scalar_t__* data; int complete; struct adb_request* next; scalar_t__ reply_len; scalar_t__ sent; } ;

/* Variables and functions */
 scalar_t__ ADB_PACKET ; 
 int EINVAL ; 
 int /*<<< orphan*/  adb_iop_start () ; 
 scalar_t__ adb_iop_state ; 
 struct adb_request* current_req ; 
 scalar_t__ idle ; 
 struct adb_request* last_req ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int adb_iop_write(struct adb_request *req)
{
	unsigned long flags;

	if ((req->nbytes < 2) || (req->data[0] != ADB_PACKET)) {
		req->complete = 1;
		return -EINVAL;
	}

	local_irq_save(flags);

	req->next = NULL;
	req->sent = 0;
	req->complete = 0;
	req->reply_len = 0;

	if (current_req != 0) {
		last_req->next = req;
		last_req = req;
	} else {
		current_req = req;
		last_req = req;
	}

	local_irq_restore(flags);

	if (adb_iop_state == idle)
		adb_iop_start();
	return 0;
}