#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qed_spq_entry {int dummy; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_ll2_tx_queue {int /*<<< orphan*/  db_msg; int /*<<< orphan*/  doorbell_addr; } ;
struct qed_ll2_info {int /*<<< orphan*/  cid; struct qed_ll2_tx_queue tx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_1__ hw_info; int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_RAMROD_TX_QUEUE_STOP ; 
 int EINVAL ; 
 int /*<<< orphan*/  PROTOCOLID_CORE ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_db_recovery_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_sp_ll2_tx_queue_stop(struct qed_hwfn *p_hwfn,
				    struct qed_ll2_info *p_ll2_conn)
{
	struct qed_ll2_tx_queue *p_tx = &p_ll2_conn->tx_queue;
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	int rc = -EINVAL;
	qed_db_recovery_del(p_hwfn->cdev, p_tx->doorbell_addr, &p_tx->db_msg);

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_ll2_conn->cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 CORE_RAMROD_TX_QUEUE_STOP,
				 PROTOCOLID_CORE, &init_data);
	if (rc)
		return rc;

	return qed_spq_post(p_hwfn, p_ent, NULL);
}