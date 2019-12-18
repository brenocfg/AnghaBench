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
struct rx_queue_stop_ramrod_data {int complete_cqe_flg; int complete_event_flg; int /*<<< orphan*/  rx_queue_id; int /*<<< orphan*/  vport_id; } ;
struct TYPE_3__ {struct rx_queue_stop_ramrod_data rx_queue_stop; } ;
struct qed_spq_entry {TYPE_1__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_id; int /*<<< orphan*/  vport_id; } ;
struct qed_queue_cid {scalar_t__ vfid; TYPE_2__ abs; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RAMROD_RX_QUEUE_STOP ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 scalar_t__ QED_QUEUE_CID_SELF ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_eth_pf_rx_queue_stop(struct qed_hwfn *p_hwfn,
			 struct qed_queue_cid *p_cid,
			 bool b_eq_completion_only, bool b_cqe_completion)
{
	struct rx_queue_stop_ramrod_data *p_ramrod = NULL;
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	int rc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_RX_QUEUE_STOP,
				 PROTOCOLID_ETH, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.rx_queue_stop;
	p_ramrod->vport_id = p_cid->abs.vport_id;
	p_ramrod->rx_queue_id = cpu_to_le16(p_cid->abs.queue_id);

	/* Cleaning the queue requires the completion to arrive there.
	 * In addition, VFs require the answer to come as eqe to PF.
	 */
	p_ramrod->complete_cqe_flg = ((p_cid->vfid == QED_QUEUE_CID_SELF) &&
				      !b_eq_completion_only) ||
				     b_cqe_completion;
	p_ramrod->complete_event_flg = (p_cid->vfid != QED_QUEUE_CID_SELF) ||
				       b_eq_completion_only;

	return qed_spq_post(p_hwfn, p_ent, NULL);
}