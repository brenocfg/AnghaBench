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
struct scsi_cmnd {int result; scalar_t__ sc_data_direction; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  device; } ;
struct fc_stats {int /*<<< orphan*/  ControlRequests; int /*<<< orphan*/  OutputBytes; int /*<<< orphan*/  OutputRequests; int /*<<< orphan*/  InputBytes; int /*<<< orphan*/  InputRequests; } ;
struct fc_rport {scalar_t__ dd_data; } ;
struct fc_remote_port {int dummy; } ;
struct fc_lport {int /*<<< orphan*/  stats; TYPE_1__* host; scalar_t__ qfull; } ;
struct fc_fcp_pkt {int /*<<< orphan*/  state; scalar_t__ req_flags; scalar_t__ data_len; scalar_t__ xfer_len; struct fc_rport* rport; struct scsi_cmnd* cmd; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  can_queue; } ;

/* Variables and functions */
 int DID_IMM_RETRY ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FC_SRB_FREE ; 
 scalar_t__ FC_SRB_READ ; 
 scalar_t__ FC_SRB_WRITE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 scalar_t__ fc_fcp_can_queue_ramp_down (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_fcp_lport_queue_ready (struct fc_lport*) ; 
 struct fc_fcp_pkt* fc_fcp_pkt_alloc (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_fcp_pkt_release (struct fc_fcp_pkt*) ; 
 int fc_fcp_pkt_send (struct fc_lport*,struct fc_fcp_pkt*) ; 
 int fc_remote_port_chkready (struct fc_rport*) ; 
 int /*<<< orphan*/  get_cpu () ; 
 struct fc_stats* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu () ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_cmnd*) ; 

int fc_queuecommand(struct Scsi_Host *shost, struct scsi_cmnd *sc_cmd)
{
	struct fc_lport *lport = shost_priv(shost);
	struct fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	struct fc_fcp_pkt *fsp;
	int rval;
	int rc = 0;
	struct fc_stats *stats;

	rval = fc_remote_port_chkready(rport);
	if (rval) {
		sc_cmd->result = rval;
		sc_cmd->scsi_done(sc_cmd);
		return 0;
	}

	if (!*(struct fc_remote_port **)rport->dd_data) {
		/*
		 * rport is transitioning from blocked/deleted to
		 * online
		 */
		sc_cmd->result = DID_IMM_RETRY << 16;
		sc_cmd->scsi_done(sc_cmd);
		goto out;
	}

	if (!fc_fcp_lport_queue_ready(lport)) {
		if (lport->qfull) {
			if (fc_fcp_can_queue_ramp_down(lport))
				shost_printk(KERN_ERR, lport->host,
					     "libfc: queue full, "
					     "reducing can_queue to %d.\n",
					     lport->host->can_queue);
		}
		rc = SCSI_MLQUEUE_HOST_BUSY;
		goto out;
	}

	fsp = fc_fcp_pkt_alloc(lport, GFP_ATOMIC);
	if (fsp == NULL) {
		rc = SCSI_MLQUEUE_HOST_BUSY;
		goto out;
	}

	/*
	 * build the libfc request pkt
	 */
	fsp->cmd = sc_cmd;	/* save the cmd */
	fsp->rport = rport;	/* set the remote port ptr */

	/*
	 * set up the transfer length
	 */
	fsp->data_len = scsi_bufflen(sc_cmd);
	fsp->xfer_len = 0;

	/*
	 * setup the data direction
	 */
	stats = per_cpu_ptr(lport->stats, get_cpu());
	if (sc_cmd->sc_data_direction == DMA_FROM_DEVICE) {
		fsp->req_flags = FC_SRB_READ;
		stats->InputRequests++;
		stats->InputBytes += fsp->data_len;
	} else if (sc_cmd->sc_data_direction == DMA_TO_DEVICE) {
		fsp->req_flags = FC_SRB_WRITE;
		stats->OutputRequests++;
		stats->OutputBytes += fsp->data_len;
	} else {
		fsp->req_flags = 0;
		stats->ControlRequests++;
	}
	put_cpu();

	/*
	 * send it to the lower layer
	 * if we get -1 return then put the request in the pending
	 * queue.
	 */
	rval = fc_fcp_pkt_send(lport, fsp);
	if (rval != 0) {
		fsp->state = FC_SRB_FREE;
		fc_fcp_pkt_release(fsp);
		rc = SCSI_MLQUEUE_HOST_BUSY;
	}
out:
	return rc;
}