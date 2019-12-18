#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtio_scsi_cmd_resp {int response; scalar_t__ sense_len; int /*<<< orphan*/  sense; scalar_t__ resid; int /*<<< orphan*/  status; } ;
struct TYPE_3__ {struct virtio_scsi_cmd_resp cmd; } ;
struct virtio_scsi_cmd {TYPE_1__ resp; struct scsi_cmnd* sc; } ;
struct virtio_scsi {int /*<<< orphan*/  vdev; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;scalar_t__ sense_buffer; int /*<<< orphan*/  result; TYPE_2__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  sdev_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ABORT ; 
 int /*<<< orphan*/  DID_BAD_TARGET ; 
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  DID_NEXUS_FAILURE ; 
 int /*<<< orphan*/  DID_OK ; 
 int /*<<< orphan*/  DID_RESET ; 
 int /*<<< orphan*/  DID_TARGET_FAILURE ; 
 int /*<<< orphan*/  DID_TRANSPORT_DISRUPTED ; 
 int /*<<< orphan*/  DRIVER_SENSE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ VIRTIO_SCSI_SENSE_SIZE ; 
#define  VIRTIO_SCSI_S_ABORTED 137 
#define  VIRTIO_SCSI_S_BAD_TARGET 136 
#define  VIRTIO_SCSI_S_BUSY 135 
#define  VIRTIO_SCSI_S_FAILURE 134 
#define  VIRTIO_SCSI_S_NEXUS_FAILURE 133 
#define  VIRTIO_SCSI_S_OK 132 
#define  VIRTIO_SCSI_S_OVERRUN 131 
#define  VIRTIO_SCSI_S_RESET 130 
#define  VIRTIO_SCSI_S_TARGET_FAILURE 129 
#define  VIRTIO_SCSI_S_TRANSPORT_FAILURE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct scsi_cmnd*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int) ; 
 int /*<<< orphan*/  set_driver_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  u32 ; 
 scalar_t__ virtio32_to_cpu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  virtscsi_compute_resid (struct scsi_cmnd*,scalar_t__) ; 

__attribute__((used)) static void virtscsi_complete_cmd(struct virtio_scsi *vscsi, void *buf)
{
	struct virtio_scsi_cmd *cmd = buf;
	struct scsi_cmnd *sc = cmd->sc;
	struct virtio_scsi_cmd_resp *resp = &cmd->resp.cmd;

	dev_dbg(&sc->device->sdev_gendev,
		"cmd %p response %u status %#02x sense_len %u\n",
		sc, resp->response, resp->status, resp->sense_len);

	sc->result = resp->status;
	virtscsi_compute_resid(sc, virtio32_to_cpu(vscsi->vdev, resp->resid));
	switch (resp->response) {
	case VIRTIO_SCSI_S_OK:
		set_host_byte(sc, DID_OK);
		break;
	case VIRTIO_SCSI_S_OVERRUN:
		set_host_byte(sc, DID_ERROR);
		break;
	case VIRTIO_SCSI_S_ABORTED:
		set_host_byte(sc, DID_ABORT);
		break;
	case VIRTIO_SCSI_S_BAD_TARGET:
		set_host_byte(sc, DID_BAD_TARGET);
		break;
	case VIRTIO_SCSI_S_RESET:
		set_host_byte(sc, DID_RESET);
		break;
	case VIRTIO_SCSI_S_BUSY:
		set_host_byte(sc, DID_BUS_BUSY);
		break;
	case VIRTIO_SCSI_S_TRANSPORT_FAILURE:
		set_host_byte(sc, DID_TRANSPORT_DISRUPTED);
		break;
	case VIRTIO_SCSI_S_TARGET_FAILURE:
		set_host_byte(sc, DID_TARGET_FAILURE);
		break;
	case VIRTIO_SCSI_S_NEXUS_FAILURE:
		set_host_byte(sc, DID_NEXUS_FAILURE);
		break;
	default:
		scmd_printk(KERN_WARNING, sc, "Unknown response %d",
			    resp->response);
		/* fall through */
	case VIRTIO_SCSI_S_FAILURE:
		set_host_byte(sc, DID_ERROR);
		break;
	}

	WARN_ON(virtio32_to_cpu(vscsi->vdev, resp->sense_len) >
		VIRTIO_SCSI_SENSE_SIZE);
	if (sc->sense_buffer) {
		memcpy(sc->sense_buffer, resp->sense,
		       min_t(u32,
			     virtio32_to_cpu(vscsi->vdev, resp->sense_len),
			     VIRTIO_SCSI_SENSE_SIZE));
		if (resp->sense_len)
			set_driver_byte(sc, DRIVER_SENSE);
	}

	sc->scsi_done(sc);
}