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
struct dasd_device {scalar_t__ state; } ;
struct dasd_ccw_req {scalar_t__ status; int /*<<< orphan*/  retries; } ;

/* Variables and functions */
 scalar_t__ DASD_CQR_CLEAR_PENDING ; 
 scalar_t__ DASD_CQR_IN_IO ; 
 scalar_t__ DASD_CQR_QUEUED ; 
 int /*<<< orphan*/  DASD_EER_NOSPC ; 
 scalar_t__ DASD_STATE_BASIC ; 
 int /*<<< orphan*/  DASD_STOPPED_NOSPC ; 
 int /*<<< orphan*/  dasd_device_clear_timer (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_device_set_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eer_write (struct dasd_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 

void dasd_generic_space_exhaust(struct dasd_device *device,
				struct dasd_ccw_req *cqr)
{
	dasd_eer_write(device, NULL, DASD_EER_NOSPC);

	if (device->state < DASD_STATE_BASIC)
		return;

	if (cqr->status == DASD_CQR_IN_IO ||
	    cqr->status == DASD_CQR_CLEAR_PENDING) {
		cqr->status = DASD_CQR_QUEUED;
		cqr->retries++;
	}
	dasd_device_set_stop_bits(device, DASD_STOPPED_NOSPC);
	dasd_device_clear_timer(device);
	dasd_schedule_device_bh(device);
}