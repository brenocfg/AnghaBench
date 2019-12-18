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
struct visordisk_info {int dummy; } ;
struct scsi_device {struct visordisk_info* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct visordisk_info*) ; 

__attribute__((used)) static void visorhba_slave_destroy(struct scsi_device *scsidev)
{
	/* midlevel calls this after device has been quiesced and
	 * before it is to be deleted.
	 */
	struct visordisk_info *vdisk;

	vdisk = scsidev->hostdata;
	scsidev->hostdata = NULL;
	kfree(vdisk);
}