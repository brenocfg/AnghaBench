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
struct scsi_device {int use_10_for_rw; int use_10_for_ms; int no_write_same; int max_device_blocked; } ;

/* Variables and functions */

__attribute__((used)) static void ata_scsi_sdev_config(struct scsi_device *sdev)
{
	sdev->use_10_for_rw = 1;
	sdev->use_10_for_ms = 1;
	sdev->no_write_same = 1;

	/* Schedule policy is determined by ->qc_defer() callback and
	 * it needs to see every deferred qc.  Set dev_blocked to 1 to
	 * prevent SCSI midlayer from automatically deferring
	 * requests.
	 */
	sdev->max_device_blocked = 1;
}