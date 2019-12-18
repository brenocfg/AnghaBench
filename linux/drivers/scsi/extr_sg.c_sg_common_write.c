#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ dxfer_len; char interface_id; int flags; int /*<<< orphan*/  duration; scalar_t__ cmd_len; scalar_t__ resid; scalar_t__ driver_status; scalar_t__ host_status; scalar_t__ info; scalar_t__ msg_status; scalar_t__ masked_status; scalar_t__ status; } ;
typedef  TYPE_3__ sg_io_hdr_t ;
struct TYPE_23__ {int /*<<< orphan*/  disk; TYPE_2__* device; int /*<<< orphan*/  detaching; } ;
struct TYPE_22__ {int /*<<< orphan*/  f_ref; TYPE_6__* parentdp; } ;
struct TYPE_18__ {unsigned char cmd_opcode; } ;
struct TYPE_21__ {TYPE_14__* rq; scalar_t__ bio; TYPE_1__ data; TYPE_3__ header; } ;
struct TYPE_19__ {int /*<<< orphan*/  request_queue; } ;
struct TYPE_17__ {int timeout; } ;
typedef  TYPE_4__ Sg_request ;
typedef  TYPE_5__ Sg_fd ;
typedef  TYPE_6__ Sg_device ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_TIMEOUT (int,int /*<<< orphan*/ ) ; 
 int SG_FLAG_Q_AT_TAIL ; 
 scalar_t__ SZ_256M ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_14__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (TYPE_14__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_req (TYPE_14__*) ; 
 int /*<<< orphan*/  scsi_req_free_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_finish_rem_req (TYPE_4__*) ; 
 int /*<<< orphan*/  sg_printk (int /*<<< orphan*/ ,TYPE_6__*,char*,int,...) ; 
 int /*<<< orphan*/  sg_remove_request (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sg_rq_end_io ; 
 int sg_start_req (TYPE_4__*,unsigned char*) ; 

__attribute__((used)) static int
sg_common_write(Sg_fd * sfp, Sg_request * srp,
		unsigned char *cmnd, int timeout, int blocking)
{
	int k, at_head;
	Sg_device *sdp = sfp->parentdp;
	sg_io_hdr_t *hp = &srp->header;

	srp->data.cmd_opcode = cmnd[0];	/* hold opcode of command */
	hp->status = 0;
	hp->masked_status = 0;
	hp->msg_status = 0;
	hp->info = 0;
	hp->host_status = 0;
	hp->driver_status = 0;
	hp->resid = 0;
	SCSI_LOG_TIMEOUT(4, sg_printk(KERN_INFO, sfp->parentdp,
			"sg_common_write:  scsi opcode=0x%02x, cmd_size=%d\n",
			(int) cmnd[0], (int) hp->cmd_len));

	if (hp->dxfer_len >= SZ_256M)
		return -EINVAL;

	k = sg_start_req(srp, cmnd);
	if (k) {
		SCSI_LOG_TIMEOUT(1, sg_printk(KERN_INFO, sfp->parentdp,
			"sg_common_write: start_req err=%d\n", k));
		sg_finish_rem_req(srp);
		sg_remove_request(sfp, srp);
		return k;	/* probably out of space --> ENOMEM */
	}
	if (atomic_read(&sdp->detaching)) {
		if (srp->bio) {
			scsi_req_free_cmd(scsi_req(srp->rq));
			blk_put_request(srp->rq);
			srp->rq = NULL;
		}

		sg_finish_rem_req(srp);
		sg_remove_request(sfp, srp);
		return -ENODEV;
	}

	hp->duration = jiffies_to_msecs(jiffies);
	if (hp->interface_id != '\0' &&	/* v3 (or later) interface */
	    (SG_FLAG_Q_AT_TAIL & hp->flags))
		at_head = 0;
	else
		at_head = 1;

	srp->rq->timeout = timeout;
	kref_get(&sfp->f_ref); /* sg_rq_end_io() does kref_put(). */
	blk_execute_rq_nowait(sdp->device->request_queue, sdp->disk,
			      srp->rq, at_head, sg_rq_end_io);
	return 0;
}