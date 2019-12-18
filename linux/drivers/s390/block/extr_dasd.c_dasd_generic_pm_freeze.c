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
struct dasd_device {TYPE_1__* discipline; int /*<<< orphan*/  flags; } ;
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* freeze ) (struct dasd_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_SUSPENDED ; 
 int /*<<< orphan*/  DASD_STOPPED_PM ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int PTR_ERR (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_device_set_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int dasd_generic_requeue_all_requests (struct dasd_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*) ; 

int dasd_generic_pm_freeze(struct ccw_device *cdev)
{
	struct dasd_device *device = dasd_device_from_cdev(cdev);

	if (IS_ERR(device))
		return PTR_ERR(device);

	/* mark device as suspended */
	set_bit(DASD_FLAG_SUSPENDED, &device->flags);

	if (device->discipline->freeze)
		device->discipline->freeze(device);

	/* disallow new I/O  */
	dasd_device_set_stop_bits(device, DASD_STOPPED_PM);

	return dasd_generic_requeue_all_requests(device);
}