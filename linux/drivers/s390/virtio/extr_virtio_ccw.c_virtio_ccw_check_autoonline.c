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
struct ccw_device {int dummy; } ;
struct ccw_dev_id {size_t ssid; int /*<<< orphan*/  devno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_device_get_id (struct ccw_device*,struct ccw_dev_id*) ; 
 int /*<<< orphan*/ * devs_no_auto ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_ccw_check_autoonline(struct ccw_device *cdev)
{
	struct ccw_dev_id id;

	ccw_device_get_id(cdev, &id);
	if (test_bit(id.devno, devs_no_auto[id.ssid]))
		return 0;
	return 1;
}