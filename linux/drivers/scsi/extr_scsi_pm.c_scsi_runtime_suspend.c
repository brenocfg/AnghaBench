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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 scalar_t__ scsi_is_sdev_device (struct device*) ; 
 int sdev_runtime_suspend (struct device*) ; 

__attribute__((used)) static int scsi_runtime_suspend(struct device *dev)
{
	int err = 0;

	dev_dbg(dev, "scsi_runtime_suspend\n");
	if (scsi_is_sdev_device(dev))
		err = sdev_runtime_suspend(dev);

	/* Insert hooks here for targets, hosts, and transport classes */

	return err;
}