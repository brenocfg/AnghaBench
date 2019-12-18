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
struct request {int /*<<< orphan*/  tag; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_SC_HOST_PATH_ERROR ; 
 int /*<<< orphan*/  blk_mq_complete_request (struct request*) ; 
 scalar_t__ blk_mq_request_completed (struct request*) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* nvme_req (struct request*) ; 

bool nvme_cancel_request(struct request *req, void *data, bool reserved)
{
	dev_dbg_ratelimited(((struct nvme_ctrl *) data)->device,
				"Cancelling I/O %d", req->tag);

	/* don't abort one completed request */
	if (blk_mq_request_completed(req))
		return true;

	nvme_req(req)->status = NVME_SC_HOST_PATH_ERROR;
	blk_mq_complete_request(req);
	return true;
}