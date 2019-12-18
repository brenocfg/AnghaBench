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
struct virtio_scsi_cmd_req {int* lun; scalar_t__ crn; scalar_t__ prio; int /*<<< orphan*/  task_attr; int /*<<< orphan*/  tag; } ;
struct virtio_device {int dummy; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_2__ {int id; int lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_SCSI_S_SIMPLE ; 
 int /*<<< orphan*/  cpu_to_virtio64 (struct virtio_device*,unsigned long) ; 

__attribute__((used)) static void virtio_scsi_init_hdr(struct virtio_device *vdev,
				 struct virtio_scsi_cmd_req *cmd,
				 struct scsi_cmnd *sc)
{
	cmd->lun[0] = 1;
	cmd->lun[1] = sc->device->id;
	cmd->lun[2] = (sc->device->lun >> 8) | 0x40;
	cmd->lun[3] = sc->device->lun & 0xff;
	cmd->tag = cpu_to_virtio64(vdev, (unsigned long)sc);
	cmd->task_attr = VIRTIO_SCSI_S_SIMPLE;
	cmd->prio = 0;
	cmd->crn = 0;
}