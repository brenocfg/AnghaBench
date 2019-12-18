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
typedef  int /*<<< orphan*/  u8 ;
struct subchannel {int dummy; } ;
struct irb {int dummy; } ;
struct ccw_request {int /*<<< orphan*/  timeout; scalar_t__ mask; int /*<<< orphan*/  retries; struct ccw1* cp; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; TYPE_1__ dev; } ;
struct ccw1 {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dma_area; struct ccw_request req; } ;
struct TYPE_5__ {int /*<<< orphan*/  irb; } ;

/* Variables and functions */
 int EACCES ; 
 int ENODEV ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccwreq_next_path (struct ccw_device*) ; 
 int /*<<< orphan*/  ccwreq_stop (struct ccw_device*,int) ; 
 int cio_clear (struct subchannel*) ; 
 int cio_start (struct subchannel*,struct ccw1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccwreq_do(struct ccw_device *cdev)
{
	struct ccw_request *req = &cdev->private->req;
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw1 *cp = req->cp;
	int rc = -EACCES;

	while (req->mask) {
		if (req->retries-- == 0) {
			/* Retries exhausted, try next path. */
			ccwreq_next_path(cdev);
			continue;
		}
		/* Perform start function. */
		memset(&cdev->private->dma_area->irb, 0, sizeof(struct irb));
		rc = cio_start(sch, cp, (u8) req->mask);
		if (rc == 0) {
			/* I/O started successfully. */
			ccw_device_set_timeout(cdev, req->timeout);
			return;
		}
		if (rc == -ENODEV) {
			/* Permanent device error. */
			break;
		}
		if (rc == -EACCES) {
			/* Permant path error. */
			ccwreq_next_path(cdev);
			continue;
		}
		/* Temporary improper status. */
		rc = cio_clear(sch);
		if (rc)
			break;
		return;
	}
	ccwreq_stop(cdev, rc);
}