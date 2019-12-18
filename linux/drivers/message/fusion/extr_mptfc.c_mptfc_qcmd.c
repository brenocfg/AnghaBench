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
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_2__* device; } ;
struct mptfc_rport_info {int dummy; } ;
struct fc_rport {scalar_t__ dd_data; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vtarget; } ;
typedef  TYPE_1__ VirtDevice ;
struct TYPE_4__ {TYPE_1__* hostdata; } ;

/* Variables and functions */
 int DID_IMM_RETRY ; 
 int DID_NO_CONNECT ; 
 int fc_remote_port_chkready (struct fc_rport*) ; 
 int mptscsih_qcmd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_target (TYPE_2__*) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub3 (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
mptfc_qcmd(struct Scsi_Host *shost, struct scsi_cmnd *SCpnt)
{
	struct mptfc_rport_info	*ri;
	struct fc_rport	*rport = starget_to_rport(scsi_target(SCpnt->device));
	int		err;
	VirtDevice	*vdevice = SCpnt->device->hostdata;

	if (!vdevice || !vdevice->vtarget) {
		SCpnt->result = DID_NO_CONNECT << 16;
		SCpnt->scsi_done(SCpnt);
		return 0;
	}

	err = fc_remote_port_chkready(rport);
	if (unlikely(err)) {
		SCpnt->result = err;
		SCpnt->scsi_done(SCpnt);
		return 0;
	}

	/* dd_data is null until finished adding target */
	ri = *((struct mptfc_rport_info **)rport->dd_data);
	if (unlikely(!ri)) {
		SCpnt->result = DID_IMM_RETRY << 16;
		SCpnt->scsi_done(SCpnt);
		return 0;
	}

	return mptscsih_qcmd(SCpnt);
}