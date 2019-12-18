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
struct dasd_device {int stopped; TYPE_1__* discipline; } ;
struct TYPE_2__ {int (* verify_path ) (struct dasd_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DASD_STOPPED_DC_WAIT ; 
 int DASD_UNRESUMED_PM ; 
 int /*<<< orphan*/  dasd_device_set_timer (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_path_clear_all_verify (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_get_tbvpm (struct dasd_device*) ; 
 int stub1 (struct dasd_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dasd_device_check_path_events(struct dasd_device *device)
{
	int rc;

	if (!dasd_path_get_tbvpm(device))
		return;

	if (device->stopped &
	    ~(DASD_STOPPED_DC_WAIT | DASD_UNRESUMED_PM))
		return;
	rc = device->discipline->verify_path(device,
					     dasd_path_get_tbvpm(device));
	if (rc)
		dasd_device_set_timer(device, 50);
	else
		dasd_path_clear_all_verify(device);
}