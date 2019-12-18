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
struct scsi_device {scalar_t__ type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 scalar_t__ TYPE_ENCLOSURE ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int ses_probe(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	int err = -ENODEV;

	if (sdev->type != TYPE_ENCLOSURE)
		goto out;

	err = 0;
	sdev_printk(KERN_NOTICE, sdev, "Attached Enclosure device\n");

 out:
	return err;
}