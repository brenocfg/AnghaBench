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
typedef  int u16 ;
struct ccw_request {int mask; int /*<<< orphan*/  lpm; int /*<<< orphan*/  maxretries; int /*<<< orphan*/  retries; int /*<<< orphan*/  singlepath; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {struct ccw_request req; } ;

/* Variables and functions */
 int lpm_adjust (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 ccwreq_next_path(struct ccw_device *cdev)
{
	struct ccw_request *req = &cdev->private->req;

	if (!req->singlepath) {
		req->mask = 0;
		goto out;
	}
	req->retries	= req->maxretries;
	req->mask	= lpm_adjust(req->mask >> 1, req->lpm);
out:
	return req->mask;
}