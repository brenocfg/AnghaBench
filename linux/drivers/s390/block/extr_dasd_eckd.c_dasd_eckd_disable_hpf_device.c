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
struct dasd_eckd_private {scalar_t__ fcx_max_data; } ;
struct dasd_device {TYPE_1__* cdev; struct dasd_eckd_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void dasd_eckd_disable_hpf_device(struct dasd_device *device)
{
	struct dasd_eckd_private *private = device->private;

	dev_err(&device->cdev->dev,
		"High Performance FICON disabled\n");
	private->fcx_max_data = 0;
}