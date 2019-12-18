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
struct virtio_scsi {int dummy; } ;
struct virtio_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_SCSI_F_HOTPLUG ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct virtio_scsi* shost_priv (struct Scsi_Host*) ; 
 scalar_t__ virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* virtio_scsi_host (struct virtio_device*) ; 
 int /*<<< orphan*/  virtscsi_cancel_event_work (struct virtio_scsi*) ; 
 int /*<<< orphan*/  virtscsi_remove_vqs (struct virtio_device*) ; 

__attribute__((used)) static void virtscsi_remove(struct virtio_device *vdev)
{
	struct Scsi_Host *shost = virtio_scsi_host(vdev);
	struct virtio_scsi *vscsi = shost_priv(shost);

	if (virtio_has_feature(vdev, VIRTIO_SCSI_F_HOTPLUG))
		virtscsi_cancel_event_work(vscsi);

	scsi_remove_host(shost);
	virtscsi_remove_vqs(vdev);
	scsi_host_put(shost);
}