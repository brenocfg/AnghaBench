#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct adb_request {int nbytes; scalar_t__ complete; struct adb_request* next; scalar_t__ reply_len; scalar_t__ sent; int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int /*<<< orphan*/  r; } ;
struct TYPE_4__ {TYPE_1__ ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_PACKET ; 
 int EINVAL ; 
 int TAR ; 
 TYPE_2__* adb ; 
 struct adb_request* current_req ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 struct adb_request* last_req ; 
 int /*<<< orphan*/  macio_adb_poll () ; 
 int /*<<< orphan*/  macio_lock ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int macio_send_request(struct adb_request *req, int sync)
{
	unsigned long flags;
	int i;
	
	if (req->data[0] != ADB_PACKET)
		return -EINVAL;
	
	for (i = 0; i < req->nbytes - 1; ++i)
		req->data[i] = req->data[i+1];
	--req->nbytes;
	
	req->next = NULL;
	req->sent = 0;
	req->complete = 0;
	req->reply_len = 0;

	spin_lock_irqsave(&macio_lock, flags);
	if (current_req != 0) {
		last_req->next = req;
		last_req = req;
	} else {
		current_req = last_req = req;
		out_8(&adb->ctrl.r, in_8(&adb->ctrl.r) | TAR);
	}
	spin_unlock_irqrestore(&macio_lock, flags);
	
	if (sync) {
		while (!req->complete)
			macio_adb_poll();
	}

	return 0;
}