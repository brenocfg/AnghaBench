#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_9__ {TYPE_2__* vtarget; } ;
typedef  TYPE_3__ VirtDevice ;
struct TYPE_11__ {int debug_level; scalar_t__ sas_discovery_quiesce_io; } ;
struct TYPE_10__ {TYPE_5__* ioc; } ;
struct TYPE_8__ {scalar_t__ deleted; } ;
struct TYPE_7__ {TYPE_3__* hostdata; } ;
typedef  TYPE_4__ MPT_SCSI_HOST ;
typedef  TYPE_5__ MPT_ADAPTER ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int MPT_DEBUG_SCSI ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int mptscsih_qcmd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 TYPE_4__* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int
mptsas_qcmd(struct Scsi_Host *shost, struct scsi_cmnd *SCpnt)
{
	MPT_SCSI_HOST	*hd;
	MPT_ADAPTER	*ioc;
	VirtDevice	*vdevice = SCpnt->device->hostdata;

	if (!vdevice || !vdevice->vtarget || vdevice->vtarget->deleted) {
		SCpnt->result = DID_NO_CONNECT << 16;
		SCpnt->scsi_done(SCpnt);
		return 0;
	}

	hd = shost_priv(shost);
	ioc = hd->ioc;

	if (ioc->sas_discovery_quiesce_io)
		return SCSI_MLQUEUE_HOST_BUSY;

	if (ioc->debug_level & MPT_DEBUG_SCSI)
		scsi_print_command(SCpnt);

	return mptscsih_qcmd(SCpnt);
}