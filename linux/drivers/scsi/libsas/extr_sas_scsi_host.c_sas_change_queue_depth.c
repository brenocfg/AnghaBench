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
struct scsi_device {int /*<<< orphan*/  tagged_supported; } ;
struct TYPE_2__ {int /*<<< orphan*/  ap; } ;
struct domain_device {TYPE_1__ sata_dev; } ;

/* Variables and functions */
 int __ata_change_queue_depth (int /*<<< orphan*/ ,struct scsi_device*,int) ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 int scsi_change_queue_depth (struct scsi_device*,int) ; 
 struct domain_device* sdev_to_domain_dev (struct scsi_device*) ; 

int sas_change_queue_depth(struct scsi_device *sdev, int depth)
{
	struct domain_device *dev = sdev_to_domain_dev(sdev);

	if (dev_is_sata(dev))
		return __ata_change_queue_depth(dev->sata_dev.ap, sdev, depth);

	if (!sdev->tagged_supported)
		depth = 1;
	return scsi_change_queue_depth(sdev, depth);
}