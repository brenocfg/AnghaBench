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
struct TYPE_7__ {void* port_name; int /*<<< orphan*/  port_id; void* node_name; } ;
struct ibmvfc_target {int /*<<< orphan*/  kref; int /*<<< orphan*/  service_parms_change; int /*<<< orphan*/  service_parms; int /*<<< orphan*/  scsi_id; TYPE_3__ ids; } ;
struct TYPE_8__ {int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct ibmvfc_port_login {int /*<<< orphan*/  fc_explain; int /*<<< orphan*/  fc_type; int /*<<< orphan*/  error; int /*<<< orphan*/  status; TYPE_4__ service_parms_change; TYPE_4__ service_parms; TYPE_2__ common; } ;
struct ibmvfc_host {int reinit; int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  discovery_threads; } ;
struct ibmvfc_event {TYPE_1__* xfer_iu; struct ibmvfc_host* vhost; struct ibmvfc_target* tgt; } ;
struct TYPE_5__ {struct ibmvfc_port_login plogi; } ;

/* Variables and functions */
 int IBMVFC_DEFAULT_LOG_LEVEL ; 
#define  IBMVFC_MAD_CRQ_ERROR 131 
#define  IBMVFC_MAD_DRIVER_FAILED 130 
#define  IBMVFC_MAD_FAILED 129 
#define  IBMVFC_MAD_SUCCESS 128 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_DEL_RPORT ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_NONE ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_get_cmd_error (int,int) ; 
 int /*<<< orphan*/  ibmvfc_get_fc_type (int) ; 
 int /*<<< orphan*/  ibmvfc_get_ls_explain (int) ; 
 int /*<<< orphan*/  ibmvfc_init_tgt (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 int /*<<< orphan*/  ibmvfc_retry_cmd (int,int) ; 
 int ibmvfc_retry_tgt_init (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_tgt_send_plogi ; 
 int /*<<< orphan*/  ibmvfc_tgt_send_prli ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 
 int /*<<< orphan*/  tgt_log (struct ibmvfc_target*,int,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 void* wwn_to_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmvfc_tgt_plogi_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_target *tgt = evt->tgt;
	struct ibmvfc_host *vhost = evt->vhost;
	struct ibmvfc_port_login *rsp = &evt->xfer_iu->plogi;
	u32 status = be16_to_cpu(rsp->common.status);
	int level = IBMVFC_DEFAULT_LOG_LEVEL;

	vhost->discovery_threads--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	switch (status) {
	case IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Port Login succeeded\n");
		if (tgt->ids.port_name &&
		    tgt->ids.port_name != wwn_to_u64(rsp->service_parms.port_name)) {
			vhost->reinit = 1;
			tgt_dbg(tgt, "Port re-init required\n");
			break;
		}
		tgt->ids.node_name = wwn_to_u64(rsp->service_parms.node_name);
		tgt->ids.port_name = wwn_to_u64(rsp->service_parms.port_name);
		tgt->ids.port_id = tgt->scsi_id;
		memcpy(&tgt->service_parms, &rsp->service_parms,
		       sizeof(tgt->service_parms));
		memcpy(&tgt->service_parms_change, &rsp->service_parms_change,
		       sizeof(tgt->service_parms_change));
		ibmvfc_init_tgt(tgt, ibmvfc_tgt_send_prli);
		break;
	case IBMVFC_MAD_DRIVER_FAILED:
		break;
	case IBMVFC_MAD_CRQ_ERROR:
		ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_plogi);
		break;
	case IBMVFC_MAD_FAILED:
	default:
		if (ibmvfc_retry_cmd(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)))
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_plogi);
		else
			ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);

		tgt_log(tgt, level, "Port Login failed: %s (%x:%x) %s (%x) %s (%x) rc=0x%02X\n",
			ibmvfc_get_cmd_error(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)),
					     be16_to_cpu(rsp->status), be16_to_cpu(rsp->error),
			ibmvfc_get_fc_type(be16_to_cpu(rsp->fc_type)), be16_to_cpu(rsp->fc_type),
			ibmvfc_get_ls_explain(be16_to_cpu(rsp->fc_explain)), be16_to_cpu(rsp->fc_explain), status);
		break;
	}

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_free_event(evt);
	wake_up(&vhost->work_wait_q);
}