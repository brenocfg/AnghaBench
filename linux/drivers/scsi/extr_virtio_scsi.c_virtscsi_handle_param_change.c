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
typedef  int u8 ;
struct virtio_scsi_event {unsigned int* lun; int /*<<< orphan*/  reason; } ;
struct virtio_scsi {int /*<<< orphan*/  vdev; } ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct scsi_device* scsi_device_lookup (struct Scsi_Host*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_rescan_device (int /*<<< orphan*/ *) ; 
 int virtio32_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* virtio_scsi_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtscsi_handle_param_change(struct virtio_scsi *vscsi,
					 struct virtio_scsi_event *event)
{
	struct scsi_device *sdev;
	struct Scsi_Host *shost = virtio_scsi_host(vscsi->vdev);
	unsigned int target = event->lun[1];
	unsigned int lun = (event->lun[2] << 8) | event->lun[3];
	u8 asc = virtio32_to_cpu(vscsi->vdev, event->reason) & 255;
	u8 ascq = virtio32_to_cpu(vscsi->vdev, event->reason) >> 8;

	sdev = scsi_device_lookup(shost, 0, target, lun);
	if (!sdev) {
		pr_err("SCSI device %d 0 %d %d not found\n",
			shost->host_no, target, lun);
		return;
	}

	/* Handle "Parameters changed", "Mode parameters changed", and
	   "Capacity data has changed".  */
	if (asc == 0x2a && (ascq == 0x00 || ascq == 0x01 || ascq == 0x09))
		scsi_rescan_device(&sdev->sdev_gendev);

	scsi_device_put(sdev);
}