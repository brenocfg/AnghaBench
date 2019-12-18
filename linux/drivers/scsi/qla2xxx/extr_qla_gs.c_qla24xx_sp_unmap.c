#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * rsp; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  rsp_allocated_size; int /*<<< orphan*/ * req; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  req_allocated_size; } ;
struct TYPE_15__ {TYPE_3__ ctarg; int /*<<< orphan*/  els_plogi; } ;
struct srb_iocb {TYPE_4__ u; } ;
struct TYPE_16__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_17__ {int type; int /*<<< orphan*/  (* free ) (TYPE_6__*) ;TYPE_5__ u; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_18__ {TYPE_2__* hw; } ;
typedef  TYPE_7__ scsi_qla_host_t ;
struct TYPE_13__ {TYPE_1__* pdev; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SRB_CT_PTHRU_CMD 129 
#define  SRB_ELS_DCMD 128 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_els_dcmd2_free (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 

void qla24xx_sp_unmap(scsi_qla_host_t *vha, srb_t *sp)
{
	struct srb_iocb *c = &sp->u.iocb_cmd;

	switch (sp->type) {
	case SRB_ELS_DCMD:
		qla2x00_els_dcmd2_free(vha, &c->u.els_plogi);
		break;
	case SRB_CT_PTHRU_CMD:
	default:
		if (sp->u.iocb_cmd.u.ctarg.req) {
			dma_free_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.req,
			    sp->u.iocb_cmd.u.ctarg.req_dma);
			sp->u.iocb_cmd.u.ctarg.req = NULL;
		}

		if (sp->u.iocb_cmd.u.ctarg.rsp) {
			dma_free_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.rsp,
			    sp->u.iocb_cmd.u.ctarg.rsp_dma);
			sp->u.iocb_cmd.u.ctarg.rsp = NULL;
		}
		break;
	}

	sp->free(sp);
}