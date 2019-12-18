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
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scsi_device* class_to_sdev (struct device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scsi_device_cls_release(struct device *class_dev)
{
	struct scsi_device *sdev;

	sdev = class_to_sdev(class_dev);
	put_device(&sdev->sdev_gendev);
}