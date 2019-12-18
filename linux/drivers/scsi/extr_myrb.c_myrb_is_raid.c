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
struct scsi_device {scalar_t__ channel; int /*<<< orphan*/  host; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ myrb_logical_channel (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int myrb_is_raid(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);

	return sdev->channel == myrb_logical_channel(sdev->host);
}