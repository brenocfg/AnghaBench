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
struct irb {int dummy; } ;
struct dasd_device {TYPE_1__* discipline; TYPE_2__* cdev; } ;
struct dasd_ccw_req {int /*<<< orphan*/  intrc; struct dasd_device* startdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dump_sense ) (struct dasd_device*,struct dasd_ccw_req*,struct irb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOLINK ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*,struct dasd_ccw_req*,struct irb*) ; 

void
dasd_log_sense(struct dasd_ccw_req *cqr, struct irb *irb)
{
	struct dasd_device *device;

	device = cqr->startdev;
	if (cqr->intrc == -ETIMEDOUT) {
		dev_err(&device->cdev->dev,
			"A timeout error occurred for cqr %p\n", cqr);
		return;
	}
	if (cqr->intrc == -ENOLINK) {
		dev_err(&device->cdev->dev,
			"A transport error occurred for cqr %p\n", cqr);
		return;
	}
	/* dump sense data */
	if (device->discipline && device->discipline->dump_sense)
		device->discipline->dump_sense(device, cqr, irb);
}