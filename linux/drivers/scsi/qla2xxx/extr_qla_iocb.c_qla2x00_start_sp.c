#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct qla_qpair {int /*<<< orphan*/  qp_lock_ptr; int /*<<< orphan*/  req; } ;
struct qla_hw_data {int dummy; } ;
struct TYPE_31__ {int /*<<< orphan*/  timer; } ;
struct TYPE_32__ {TYPE_1__ iocb_cmd; } ;
struct TYPE_33__ {int type; TYPE_2__ u; scalar_t__ start_timer; struct qla_qpair* qpair; TYPE_4__* vha; } ;
typedef  TYPE_3__ srb_t ;
struct TYPE_34__ {struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLAFX00 (struct qla_hw_data*) ; 
 int QLA_SUCCESS ; 
#define  SRB_ABT_CMD 147 
#define  SRB_ADISC_CMD 146 
#define  SRB_CTRL_VP 145 
#define  SRB_CT_CMD 144 
#define  SRB_CT_PTHRU_CMD 143 
#define  SRB_ELS_CMD_HST 142 
#define  SRB_ELS_CMD_RPT 141 
#define  SRB_ELS_DCMD 140 
#define  SRB_FXIOCB_BCMD 139 
#define  SRB_FXIOCB_DCMD 138 
#define  SRB_LOGIN_CMD 137 
#define  SRB_LOGOUT_CMD 136 
#define  SRB_MB_IOCB 135 
#define  SRB_NACK_LOGO 134 
#define  SRB_NACK_PLOGI 133 
#define  SRB_NACK_PRLI 132 
#define  SRB_NVME_LS 131 
#define  SRB_PRLI_CMD 130 
#define  SRB_PRLO_CMD 129 
#define  SRB_TM_CMD 128 
 void* __qla2x00_alloc_iocbs (struct qla_qpair*,TYPE_3__*) ; 
 int /*<<< orphan*/  add_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_abort_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_adisc_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_ct_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_els_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_els_logo_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_login_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_logout_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_prli_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_prlo_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla24xx_tm_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla25xx_ctrlvp_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla2x00_adisc_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla2x00_ct_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla2x00_ctpthru_cmd_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla2x00_login_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla2x00_logout_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla2x00_mb_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla2x00_send_notify_ack_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qla2x00_start_iocbs (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_nvme_ls (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qlafx00_abort_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qlafx00_fxdisc_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  qlafx00_tm_iocb (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

int
qla2x00_start_sp(srb_t *sp)
{
	int rval = QLA_SUCCESS;
	scsi_qla_host_t *vha = sp->vha;
	struct qla_hw_data *ha = vha->hw;
	struct qla_qpair *qp = sp->qpair;
	void *pkt;
	unsigned long flags;

	spin_lock_irqsave(qp->qp_lock_ptr, flags);
	pkt = __qla2x00_alloc_iocbs(sp->qpair, sp);
	if (!pkt) {
		rval = EAGAIN;
		ql_log(ql_log_warn, vha, 0x700c,
		    "qla2x00_alloc_iocbs failed.\n");
		goto done;
	}

	switch (sp->type) {
	case SRB_LOGIN_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_login_iocb(sp, pkt) :
		    qla2x00_login_iocb(sp, pkt);
		break;
	case SRB_PRLI_CMD:
		qla24xx_prli_iocb(sp, pkt);
		break;
	case SRB_LOGOUT_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_logout_iocb(sp, pkt) :
		    qla2x00_logout_iocb(sp, pkt);
		break;
	case SRB_ELS_CMD_RPT:
	case SRB_ELS_CMD_HST:
		qla24xx_els_iocb(sp, pkt);
		break;
	case SRB_CT_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_ct_iocb(sp, pkt) :
		    qla2x00_ct_iocb(sp, pkt);
		break;
	case SRB_ADISC_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_adisc_iocb(sp, pkt) :
		    qla2x00_adisc_iocb(sp, pkt);
		break;
	case SRB_TM_CMD:
		IS_QLAFX00(ha) ?
		    qlafx00_tm_iocb(sp, pkt) :
		    qla24xx_tm_iocb(sp, pkt);
		break;
	case SRB_FXIOCB_DCMD:
	case SRB_FXIOCB_BCMD:
		qlafx00_fxdisc_iocb(sp, pkt);
		break;
	case SRB_NVME_LS:
		qla_nvme_ls(sp, pkt);
		break;
	case SRB_ABT_CMD:
		IS_QLAFX00(ha) ?
			qlafx00_abort_iocb(sp, pkt) :
			qla24xx_abort_iocb(sp, pkt);
		break;
	case SRB_ELS_DCMD:
		qla24xx_els_logo_iocb(sp, pkt);
		break;
	case SRB_CT_PTHRU_CMD:
		qla2x00_ctpthru_cmd_iocb(sp, pkt);
		break;
	case SRB_MB_IOCB:
		qla2x00_mb_iocb(sp, pkt);
		break;
	case SRB_NACK_PLOGI:
	case SRB_NACK_PRLI:
	case SRB_NACK_LOGO:
		qla2x00_send_notify_ack_iocb(sp, pkt);
		break;
	case SRB_CTRL_VP:
		qla25xx_ctrlvp_iocb(sp, pkt);
		break;
	case SRB_PRLO_CMD:
		qla24xx_prlo_iocb(sp, pkt);
		break;
	default:
		break;
	}

	if (sp->start_timer)
		add_timer(&sp->u.iocb_cmd.timer);

	wmb();
	qla2x00_start_iocbs(vha, qp->req);
done:
	spin_unlock_irqrestore(qp->qp_lock_ptr, flags);
	return rval;
}