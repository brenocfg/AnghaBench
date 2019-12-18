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
struct dasd_device {int /*<<< orphan*/  kick_validate; int /*<<< orphan*/  reload_device; } ;

/* Variables and functions */
 scalar_t__ cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 

__attribute__((used)) static int dasd_eckd_online_to_ready(struct dasd_device *device)
{
	if (cancel_work_sync(&device->reload_device))
		dasd_put_device(device);
	if (cancel_work_sync(&device->kick_validate))
		dasd_put_device(device);

	return 0;
}