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
typedef  int u8 ;
typedef  int u32 ;
struct ibmvfc_target {int /*<<< orphan*/  kref; int /*<<< orphan*/  timer; } ;
struct TYPE_8__ {int /*<<< orphan*/  error; int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/ * response; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct ibmvfc_passthru_mad {TYPE_4__ iu; TYPE_3__ fc_iu; TYPE_2__ common; } ;
struct ibmvfc_host {int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  discovery_threads; } ;
struct ibmvfc_event {TYPE_1__* xfer_iu; struct ibmvfc_host* vhost; struct ibmvfc_target* tgt; } ;
struct TYPE_5__ {struct ibmvfc_passthru_mad passthru; } ;

/* Variables and functions */
#define  IBMVFC_MAD_DRIVER_FAILED 130 
#define  IBMVFC_MAD_FAILED 129 
#define  IBMVFC_MAD_SUCCESS 128 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_DEL_RPORT ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_NONE ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmvfc_adisc_needs_plogi (struct ibmvfc_passthru_mad*,struct ibmvfc_target*) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_get_cmd_error (int,int) ; 
 int /*<<< orphan*/  ibmvfc_get_fc_type (int) ; 
 int /*<<< orphan*/  ibmvfc_get_ls_explain (int) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 
 int /*<<< orphan*/  tgt_info (struct ibmvfc_target*,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_tgt_adisc_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_target *tgt = evt->tgt;
	struct ibmvfc_host *vhost = evt->vhost;
	struct ibmvfc_passthru_mad *mad = &evt->xfer_iu->passthru;
	u32 status = be16_to_cpu(mad->common.status);
	u8 fc_reason, fc_explain;

	vhost->discovery_threads--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	del_timer(&tgt->timer);

	switch (status) {
	case IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "ADISC succeeded\n");
		if (ibmvfc_adisc_needs_plogi(mad, tgt))
			ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		break;
	case IBMVFC_MAD_DRIVER_FAILED:
		break;
	case IBMVFC_MAD_FAILED:
	default:
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		fc_reason = (be32_to_cpu(mad->fc_iu.response[1]) & 0x00ff0000) >> 16;
		fc_explain = (be32_to_cpu(mad->fc_iu.response[1]) & 0x0000ff00) >> 8;
		tgt_info(tgt, "ADISC failed: %s (%x:%x) %s (%x) %s (%x) rc=0x%02X\n",
			 ibmvfc_get_cmd_error(be16_to_cpu(mad->iu.status), be16_to_cpu(mad->iu.error)),
			 be16_to_cpu(mad->iu.status), be16_to_cpu(mad->iu.error),
			 ibmvfc_get_fc_type(fc_reason), fc_reason,
			 ibmvfc_get_ls_explain(fc_explain), fc_explain, status);
		break;
	}

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_free_event(evt);
	wake_up(&vhost->work_wait_q);
}