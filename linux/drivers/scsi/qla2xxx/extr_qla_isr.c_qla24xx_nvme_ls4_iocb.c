#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int dummy; } ;
struct req_que {int dummy; } ;
struct pt_ls4_request {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* done ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* qla2x00_get_sp_from_handle (struct scsi_qla_host*,char const*,struct req_que*,struct pt_ls4_request*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void qla24xx_nvme_ls4_iocb(struct scsi_qla_host *vha,
    struct pt_ls4_request *pkt, struct req_que *req)
{
	srb_t *sp;
	const char func[] = "LS4_IOCB";
	uint16_t comp_status;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	if (!sp)
		return;

	comp_status = le16_to_cpu(pkt->status);
	sp->done(sp, comp_status);
}