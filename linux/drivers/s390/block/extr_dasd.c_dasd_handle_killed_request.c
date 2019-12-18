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
struct dasd_device {TYPE_1__* discipline; } ;
struct dasd_ccw_req {scalar_t__ status; int /*<<< orphan*/  magic; struct dasd_device* startdev; } ;
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ebcname; } ;

/* Variables and functions */
 scalar_t__ DASD_CQR_IN_IO ; 
 char* DASD_CQR_QUEUED ; 
 int /*<<< orphan*/  DBF_DEBUG ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,struct ccw_device*,char*,char*) ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_device_clear_timer (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev_locked (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void dasd_handle_killed_request(struct ccw_device *cdev,
				       unsigned long intparm)
{
	struct dasd_ccw_req *cqr;
	struct dasd_device *device;

	if (!intparm)
		return;
	cqr = (struct dasd_ccw_req *) intparm;
	if (cqr->status != DASD_CQR_IN_IO) {
		DBF_EVENT_DEVID(DBF_DEBUG, cdev,
				"invalid status in handle_killed_request: "
				"%02x", cqr->status);
		return;
	}

	device = dasd_device_from_cdev_locked(cdev);
	if (IS_ERR(device)) {
		DBF_EVENT_DEVID(DBF_DEBUG, cdev, "%s",
				"unable to get device from cdev");
		return;
	}

	if (!cqr->startdev ||
	    device != cqr->startdev ||
	    strncmp(cqr->startdev->discipline->ebcname,
		    (char *) &cqr->magic, 4)) {
		DBF_EVENT_DEVID(DBF_DEBUG, cdev, "%s",
				"invalid device in request");
		dasd_put_device(device);
		return;
	}

	/* Schedule request to be retried. */
	cqr->status = DASD_CQR_QUEUED;

	dasd_device_clear_timer(device);
	dasd_schedule_device_bh(device);
	dasd_put_device(device);
}