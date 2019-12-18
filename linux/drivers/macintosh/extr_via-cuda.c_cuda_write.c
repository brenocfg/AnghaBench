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
 scalar_t__ CUDA_PACKET ; 
 int EINVAL ; 
 int /*<<< orphan*/  cuda_lock ; 
 int /*<<< orphan*/  cuda_start () ; 
 scalar_t__ cuda_state ; 
 struct adb_request* current_req ; 
 scalar_t__ idle ; 
 struct adb_request* last_req ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
cuda_write(struct adb_request *req)
{
    unsigned long flags;

    if (req->nbytes < 2 || req->data[0] > CUDA_PACKET) {
	req->complete = 1;
	return -EINVAL;
    }
    req->next = NULL;
    req->sent = 0;
    req->complete = 0;
    req->reply_len = 0;

    spin_lock_irqsave(&cuda_lock, flags);
    if (current_req != 0) {
	last_req->next = req;
	last_req = req;
    } else {
	current_req = req;
	last_req = req;
	if (cuda_state == idle)
	    cuda_start();
    }
    spin_unlock_irqrestore(&cuda_lock, flags);

    return 0;
}