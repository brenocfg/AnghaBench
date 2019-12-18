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
struct scsi_device {int /*<<< orphan*/  request_queue; } ;
struct device {TYPE_1__* driver; } ;
struct dev_pm_ops {int (* runtime_resume ) (struct device*) ;} ;
struct TYPE_2__ {struct dev_pm_ops* pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_post_runtime_resume (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_pre_runtime_resume (int /*<<< orphan*/ ) ; 
 int stub1 (struct device*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int sdev_runtime_resume(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	const struct dev_pm_ops *pm = dev->driver ? dev->driver->pm : NULL;
	int err = 0;

	blk_pre_runtime_resume(sdev->request_queue);
	if (pm && pm->runtime_resume)
		err = pm->runtime_resume(dev);
	blk_post_runtime_resume(sdev->request_queue, err);

	return err;
}