#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  roles; } ;
struct ibmvfc_target {int add_rport; int /*<<< orphan*/  kref; int /*<<< orphan*/  logo_rcvd; TYPE_3__ ids; int /*<<< orphan*/  need_login; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct ibmvfc_prli_svc_parms {int /*<<< orphan*/  service_parms; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct ibmvfc_process_login {int /*<<< orphan*/  error; int /*<<< orphan*/  status; TYPE_2__ common; struct ibmvfc_prli_svc_parms parms; } ;
struct ibmvfc_host {int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  discovery_threads; } ;
struct ibmvfc_event {TYPE_1__* xfer_iu; struct ibmvfc_host* vhost; struct ibmvfc_target* tgt; } ;
struct TYPE_8__ {int /*<<< orphan*/  retry; int /*<<< orphan*/  logged_in; } ;
struct TYPE_5__ {struct ibmvfc_process_login prli; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_PORT_ROLE_FCP_INITIATOR ; 
 int /*<<< orphan*/  FC_PORT_ROLE_FCP_TARGET ; 
 int IBMVFC_DEFAULT_LOG_LEVEL ; 
#define  IBMVFC_MAD_CRQ_ERROR 131 
#define  IBMVFC_MAD_DRIVER_FAILED 130 
#define  IBMVFC_MAD_FAILED 129 
#define  IBMVFC_MAD_SUCCESS 128 
 int IBMVFC_PLOGI_REQUIRED ; 
 int IBMVFC_PRLI_EST_IMG_PAIR ; 
 int IBMVFC_PRLI_INITIATOR_FUNC ; 
 int IBMVFC_PRLI_TARGET_FUNC ; 
 int /*<<< orphan*/  IBMVFC_SCSI_FCP_TYPE ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_DEL_RPORT ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_NONE ; 
 int IBMVFC_VIOS_FAILURE ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_get_cmd_error (int,int) ; 
 int ibmvfc_get_prli_rsp (int) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 int /*<<< orphan*/  ibmvfc_retry_cmd (int,int) ; 
 int ibmvfc_retry_tgt_init (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_tgt_send_plogi ; 
 int /*<<< orphan*/  ibmvfc_tgt_send_prli ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* prli_rsp ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgt_log (struct ibmvfc_target*,int,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_tgt_prli_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_target *tgt = evt->tgt;
	struct ibmvfc_host *vhost = evt->vhost;
	struct ibmvfc_process_login *rsp = &evt->xfer_iu->prli;
	struct ibmvfc_prli_svc_parms *parms = &rsp->parms;
	u32 status = be16_to_cpu(rsp->common.status);
	int index, level = IBMVFC_DEFAULT_LOG_LEVEL;

	vhost->discovery_threads--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	switch (status) {
	case IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Process Login succeeded: %X %02X %04X\n",
			parms->type, parms->flags, parms->service_parms);

		if (parms->type == IBMVFC_SCSI_FCP_TYPE) {
			index = ibmvfc_get_prli_rsp(be16_to_cpu(parms->flags));
			if (prli_rsp[index].logged_in) {
				if (be16_to_cpu(parms->flags) & IBMVFC_PRLI_EST_IMG_PAIR) {
					tgt->need_login = 0;
					tgt->ids.roles = 0;
					if (be32_to_cpu(parms->service_parms) & IBMVFC_PRLI_TARGET_FUNC)
						tgt->ids.roles |= FC_PORT_ROLE_FCP_TARGET;
					if (be32_to_cpu(parms->service_parms) & IBMVFC_PRLI_INITIATOR_FUNC)
						tgt->ids.roles |= FC_PORT_ROLE_FCP_INITIATOR;
					tgt->add_rport = 1;
				} else
					ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
			} else if (prli_rsp[index].retry)
				ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_prli);
			else
				ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		} else
			ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		break;
	case IBMVFC_MAD_DRIVER_FAILED:
		break;
	case IBMVFC_MAD_CRQ_ERROR:
		ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_prli);
		break;
	case IBMVFC_MAD_FAILED:
	default:
		if ((be16_to_cpu(rsp->status) & IBMVFC_VIOS_FAILURE) &&
		     be16_to_cpu(rsp->error) == IBMVFC_PLOGI_REQUIRED)
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_plogi);
		else if (tgt->logo_rcvd)
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_plogi);
		else if (ibmvfc_retry_cmd(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)))
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_prli);
		else
			ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);

		tgt_log(tgt, level, "Process Login failed: %s (%x:%x) rc=0x%02X\n",
			ibmvfc_get_cmd_error(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)),
			be16_to_cpu(rsp->status), be16_to_cpu(rsp->error), status);
		break;
	}

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_free_event(evt);
	wake_up(&vhost->work_wait_q);
}