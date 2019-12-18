#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {int dummy; } ;
struct event_arg {int rc; TYPE_8__* fcport; TYPE_7__* sp; } ;
struct TYPE_15__ {int* fc4_features; } ;
struct TYPE_16__ {TYPE_5__ gff_id; } ;
struct ct_sns_rsp {TYPE_6__ rsp; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* free ) (TYPE_7__*) ;TYPE_8__* fcport; int /*<<< orphan*/  name; struct scsi_qla_host* vha; } ;
typedef  TYPE_7__ srb_t ;
struct TYPE_14__ {TYPE_3__* ct_sns; } ;
struct TYPE_11__ {int /*<<< orphan*/  b24; } ;
struct TYPE_18__ {int fc4_type; int fc4f_nvme; TYPE_4__ ct_desc; int /*<<< orphan*/  flags; int /*<<< orphan*/  port_name; TYPE_1__ d_id; } ;
typedef  TYPE_8__ fc_port_t ;
typedef  int /*<<< orphan*/  ea ;
struct TYPE_12__ {struct ct_sns_rsp rsp; } ;
struct TYPE_13__ {TYPE_2__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 size_t GFF_FCP_SCSI_OFFSET ; 
 size_t GFF_NVME_OFFSET ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla24xx_handle_gffid_event (struct scsi_qla_host*,struct event_arg*) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 

void qla24xx_async_gffid_sp_done(srb_t *sp, int res)
{
	struct scsi_qla_host *vha = sp->vha;
	fc_port_t *fcport = sp->fcport;
	struct ct_sns_rsp *ct_rsp;
	struct event_arg ea;

	ql_dbg(ql_dbg_disc, vha, 0x2133,
	       "Async done-%s res %x ID %x. %8phC\n",
	       sp->name, res, fcport->d_id.b24, fcport->port_name);

	fcport->flags &= ~FCF_ASYNC_SENT;
	ct_rsp = &fcport->ct_desc.ct_sns->p.rsp;
	/*
	 * FC-GS-7, 5.2.3.12 FC-4 Features - format
	 * The format of the FC-4 Features object, as defined by the FC-4,
	 * Shall be an array of 4-bit values, one for each type code value
	 */
	if (!res) {
		if (ct_rsp->rsp.gff_id.fc4_features[GFF_FCP_SCSI_OFFSET] & 0xf) {
			/* w1 b00:03 */
			fcport->fc4_type =
			    ct_rsp->rsp.gff_id.fc4_features[GFF_FCP_SCSI_OFFSET];
			fcport->fc4_type &= 0xf;
	       }

		if (ct_rsp->rsp.gff_id.fc4_features[GFF_NVME_OFFSET] & 0xf) {
			/* w5 [00:03]/28h */
			fcport->fc4f_nvme =
			    ct_rsp->rsp.gff_id.fc4_features[GFF_NVME_OFFSET];
			fcport->fc4f_nvme &= 0xf;
		}
	}

	memset(&ea, 0, sizeof(ea));
	ea.sp = sp;
	ea.fcport = sp->fcport;
	ea.rc = res;

	qla24xx_handle_gffid_event(vha, &ea);
	sp->free(sp);
}