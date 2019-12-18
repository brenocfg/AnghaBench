#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_18__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_25__ {int els_cmd; scalar_t__ comp_status; int /*<<< orphan*/  comp; TYPE_4__* els_plogi_pyld; void* els_resp_pyld; int /*<<< orphan*/  els_resp_pyld_dma; int /*<<< orphan*/  els_plogi_pyld_dma; int /*<<< orphan*/  rx_size; int /*<<< orphan*/  tx_size; } ;
struct TYPE_32__ {TYPE_18__ els_plogi; } ;
struct srb_iocb {TYPE_7__ u; int /*<<< orphan*/  timeout; } ;
struct TYPE_28__ {int /*<<< orphan*/  data; } ;
struct qla_hw_data {TYPE_3__ plogi_els_payld; TYPE_2__* pdev; } ;
struct els_plogi_payload {int dummy; } ;
struct TYPE_26__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_33__ {char* name; int /*<<< orphan*/  (* free ) (TYPE_8__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; int /*<<< orphan*/  flags; TYPE_10__* fcport; int /*<<< orphan*/  type; TYPE_1__ u; } ;
typedef  TYPE_8__ srb_t ;
struct TYPE_31__ {int /*<<< orphan*/  b24; } ;
struct TYPE_34__ {TYPE_6__ d_id; struct qla_hw_data* hw; } ;
typedef  TYPE_9__ scsi_qla_host_t ;
struct TYPE_30__ {int /*<<< orphan*/  b24; } ;
struct TYPE_24__ {int /*<<< orphan*/  flags; TYPE_5__ d_id; int /*<<< orphan*/  loop_id; } ;
typedef  TYPE_10__ fc_port_t ;
struct TYPE_29__ {int opcode; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CS_COMPLETE ; 
 int /*<<< orphan*/  DMA_POOL_SIZE ; 
 scalar_t__ ELS_DCMD_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_ELS_DCMD ; 
 int /*<<< orphan*/  SRB_WAKEUP_ON_COMP ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,TYPE_9__*,int,char*,...) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_disc ; 
 int /*<<< orphan*/  ql_dbg_io ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,TYPE_9__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_9__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  qla2x00_els_dcmd2_free (TYPE_9__*,TYPE_18__*) ; 
 int /*<<< orphan*/  qla2x00_els_dcmd2_iocb_timeout ; 
 int /*<<< orphan*/  qla2x00_els_dcmd2_sp_done ; 
 TYPE_8__* qla2x00_get_sp (TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_8__*,scalar_t__) ; 
 int qla2x00_start_sp (TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
qla24xx_els_dcmd2_iocb(scsi_qla_host_t *vha, int els_opcode,
    fc_port_t *fcport, bool wait)
{
	srb_t *sp;
	struct srb_iocb *elsio = NULL;
	struct qla_hw_data *ha = vha->hw;
	int rval = QLA_SUCCESS;
	void	*ptr, *resp_ptr;

	/* Alloc SRB structure */
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp) {
		ql_log(ql_log_info, vha, 0x70e6,
		 "SRB allocation failed\n");
		return -ENOMEM;
	}

	elsio = &sp->u.iocb_cmd;
	ql_dbg(ql_dbg_io, vha, 0x3073,
	    "Enter: PLOGI portid=%06x\n", fcport->d_id.b24);

	fcport->flags |= FCF_ASYNC_SENT;
	sp->type = SRB_ELS_DCMD;
	sp->name = "ELS_DCMD";
	sp->fcport = fcport;

	elsio->timeout = qla2x00_els_dcmd2_iocb_timeout;
	init_completion(&elsio->u.els_plogi.comp);
	if (wait)
		sp->flags = SRB_WAKEUP_ON_COMP;

	qla2x00_init_timer(sp, ELS_DCMD_TIMEOUT + 2);

	sp->done = qla2x00_els_dcmd2_sp_done;
	elsio->u.els_plogi.tx_size = elsio->u.els_plogi.rx_size = DMA_POOL_SIZE;

	ptr = elsio->u.els_plogi.els_plogi_pyld =
	    dma_alloc_coherent(&ha->pdev->dev, DMA_POOL_SIZE,
		&elsio->u.els_plogi.els_plogi_pyld_dma, GFP_KERNEL);

	if (!elsio->u.els_plogi.els_plogi_pyld) {
		rval = QLA_FUNCTION_FAILED;
		goto out;
	}

	resp_ptr = elsio->u.els_plogi.els_resp_pyld =
	    dma_alloc_coherent(&ha->pdev->dev, DMA_POOL_SIZE,
		&elsio->u.els_plogi.els_resp_pyld_dma, GFP_KERNEL);

	if (!elsio->u.els_plogi.els_resp_pyld) {
		rval = QLA_FUNCTION_FAILED;
		goto out;
	}

	ql_dbg(ql_dbg_io, vha, 0x3073, "PLOGI %p %p\n", ptr, resp_ptr);

	memset(ptr, 0, sizeof(struct els_plogi_payload));
	memset(resp_ptr, 0, sizeof(struct els_plogi_payload));
	memcpy(elsio->u.els_plogi.els_plogi_pyld->data,
	    &ha->plogi_els_payld.data,
	    sizeof(elsio->u.els_plogi.els_plogi_pyld->data));

	elsio->u.els_plogi.els_cmd = els_opcode;
	elsio->u.els_plogi.els_plogi_pyld->opcode = els_opcode;

	ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x3073, "PLOGI buffer:\n");
	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x0109,
	    (uint8_t *)elsio->u.els_plogi.els_plogi_pyld, 0x70);

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x3074,
		    "%s PLOGI sent, hdl=%x, loopid=%x, to port_id %06x from port_id %06x\n",
		    sp->name, sp->handle, fcport->loop_id,
		    fcport->d_id.b24, vha->d_id.b24);
	}

	if (wait) {
		wait_for_completion(&elsio->u.els_plogi.comp);

		if (elsio->u.els_plogi.comp_status != CS_COMPLETE)
			rval = QLA_FUNCTION_FAILED;
	} else {
		goto done;
	}

out:
	fcport->flags &= ~(FCF_ASYNC_SENT);
	qla2x00_els_dcmd2_free(vha, &elsio->u.els_plogi);
	sp->free(sp);
done:
	return rval;
}