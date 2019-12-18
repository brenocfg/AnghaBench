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
typedef  int u32 ;
struct ibmvfc_target {int /*<<< orphan*/  kref; int /*<<< orphan*/  scsi_id; int /*<<< orphan*/  new_scsi_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct ibmvfc_query_tgt {int /*<<< orphan*/  fc_explain; int /*<<< orphan*/  fc_type; int /*<<< orphan*/  error; int /*<<< orphan*/  status; int /*<<< orphan*/  scsi_id; TYPE_2__ common; } ;
struct ibmvfc_host {int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  discovery_threads; } ;
struct ibmvfc_event {TYPE_1__* xfer_iu; struct ibmvfc_host* vhost; struct ibmvfc_target* tgt; } ;
struct TYPE_3__ {struct ibmvfc_query_tgt query_tgt; } ;

/* Variables and functions */
 int IBMVFC_DEFAULT_LOG_LEVEL ; 
 int IBMVFC_FABRIC_MAPPED ; 
#define  IBMVFC_MAD_CRQ_ERROR 131 
#define  IBMVFC_MAD_DRIVER_FAILED 130 
#define  IBMVFC_MAD_FAILED 129 
#define  IBMVFC_MAD_SUCCESS 128 
 int IBMVFC_PORT_NAME_NOT_REG ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_DEL_RPORT ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_NONE ; 
 int IBMVFC_UNABLE_TO_PERFORM_REQ ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_get_cmd_error (int,int) ; 
 int /*<<< orphan*/  ibmvfc_get_fc_type (int) ; 
 int /*<<< orphan*/  ibmvfc_get_gs_explain (int) ; 
 int /*<<< orphan*/  ibmvfc_init_tgt (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 int /*<<< orphan*/  ibmvfc_retry_cmd (int,int) ; 
 int ibmvfc_retry_tgt_init (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_tgt_adisc ; 
 int /*<<< orphan*/  ibmvfc_tgt_implicit_logout ; 
 int /*<<< orphan*/  ibmvfc_tgt_query_target ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 
 int /*<<< orphan*/  tgt_log (struct ibmvfc_target*,int,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_tgt_query_target_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_target *tgt = evt->tgt;
	struct ibmvfc_host *vhost = evt->vhost;
	struct ibmvfc_query_tgt *rsp = &evt->xfer_iu->query_tgt;
	u32 status = be16_to_cpu(rsp->common.status);
	int level = IBMVFC_DEFAULT_LOG_LEVEL;

	vhost->discovery_threads--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	switch (status) {
	case IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Query Target succeeded\n");
		tgt->new_scsi_id = be64_to_cpu(rsp->scsi_id);
		if (be64_to_cpu(rsp->scsi_id) != tgt->scsi_id)
			ibmvfc_init_tgt(tgt, ibmvfc_tgt_implicit_logout);
		else
			ibmvfc_init_tgt(tgt, ibmvfc_tgt_adisc);
		break;
	case IBMVFC_MAD_DRIVER_FAILED:
		break;
	case IBMVFC_MAD_CRQ_ERROR:
		ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_query_target);
		break;
	case IBMVFC_MAD_FAILED:
	default:
		if ((be16_to_cpu(rsp->status) & IBMVFC_FABRIC_MAPPED) == IBMVFC_FABRIC_MAPPED &&
		    be16_to_cpu(rsp->error) == IBMVFC_UNABLE_TO_PERFORM_REQ &&
		    be16_to_cpu(rsp->fc_explain) == IBMVFC_PORT_NAME_NOT_REG)
			ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		else if (ibmvfc_retry_cmd(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)))
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_query_target);
		else
			ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);

		tgt_log(tgt, level, "Query Target failed: %s (%x:%x) %s (%x) %s (%x) rc=0x%02X\n",
			ibmvfc_get_cmd_error(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)),
			be16_to_cpu(rsp->status), be16_to_cpu(rsp->error),
			ibmvfc_get_fc_type(be16_to_cpu(rsp->fc_type)), be16_to_cpu(rsp->fc_type),
			ibmvfc_get_gs_explain(be16_to_cpu(rsp->fc_explain)), be16_to_cpu(rsp->fc_explain),
			status);
		break;
	}

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_free_event(evt);
	wake_up(&vhost->work_wait_q);
}