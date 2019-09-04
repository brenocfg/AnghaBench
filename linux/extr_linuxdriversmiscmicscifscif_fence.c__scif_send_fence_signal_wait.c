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
struct scif_fence_info {scalar_t__ state; int /*<<< orphan*/  comp; } ;
struct TYPE_2__ {int /*<<< orphan*/  rma_lock; } ;
struct scif_endpt {TYPE_1__ rma_info; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ OP_FAILED ; 
 scalar_t__ OP_IN_PROGRESS ; 
 int /*<<< orphan*/  SCIF_NODE_ALIVE_TIMEOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scifdev_alive (struct scif_endpt*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _scif_send_fence_signal_wait(struct scif_endpt *ep,
					struct scif_fence_info *fence_req)
{
	int err;

retry:
	/* Wait for a SCIF_SIG_(N)ACK message */
	err = wait_for_completion_timeout(&fence_req->comp,
					  SCIF_NODE_ALIVE_TIMEOUT);
	if (!err && scifdev_alive(ep))
		goto retry;
	if (!err)
		err = -ENODEV;
	if (err > 0)
		err = 0;
	if (err < 0) {
		mutex_lock(&ep->rma_info.rma_lock);
		if (fence_req->state == OP_IN_PROGRESS)
			fence_req->state = OP_FAILED;
		mutex_unlock(&ep->rma_info.rma_lock);
	}
	if (fence_req->state == OP_FAILED && !err)
		err = -ENXIO;
	return err;
}