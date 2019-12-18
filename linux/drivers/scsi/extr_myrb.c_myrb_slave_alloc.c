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
struct scsi_device {scalar_t__ channel; scalar_t__ lun; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ENXIO ; 
 int myrb_ldev_slave_alloc (struct scsi_device*) ; 
 scalar_t__ myrb_logical_channel (int /*<<< orphan*/ ) ; 
 int myrb_pdev_slave_alloc (struct scsi_device*) ; 

__attribute__((used)) static int myrb_slave_alloc(struct scsi_device *sdev)
{
	if (sdev->channel > myrb_logical_channel(sdev->host))
		return -ENXIO;

	if (sdev->lun > 0)
		return -ENXIO;

	if (sdev->channel == myrb_logical_channel(sdev->host))
		return myrb_ldev_slave_alloc(sdev);

	return myrb_pdev_slave_alloc(sdev);
}