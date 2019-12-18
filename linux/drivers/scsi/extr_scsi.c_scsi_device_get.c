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
struct scsi_device {scalar_t__ sdev_state; int /*<<< orphan*/  sdev_gendev; TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* hostt; } ;
struct TYPE_3__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ SDEV_CANCEL ; 
 scalar_t__ SDEV_DEL ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int scsi_device_get(struct scsi_device *sdev)
{
	if (sdev->sdev_state == SDEV_DEL || sdev->sdev_state == SDEV_CANCEL)
		goto fail;
	if (!get_device(&sdev->sdev_gendev))
		goto fail;
	if (!try_module_get(sdev->host->hostt->module))
		goto fail_put_device;
	return 0;

fail_put_device:
	put_device(&sdev->sdev_gendev);
fail:
	return -ENXIO;
}