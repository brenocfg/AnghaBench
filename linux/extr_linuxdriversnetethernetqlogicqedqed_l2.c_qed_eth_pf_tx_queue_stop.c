#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qed_spq_entry {int dummy; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_queue_cid {int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RAMROD_TX_QUEUE_STOP ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_eth_pf_tx_queue_stop(struct qed_hwfn *p_hwfn, struct qed_queue_cid *p_cid)
{
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	int rc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_TX_QUEUE_STOP,
				 PROTOCOLID_ETH, &init_data);
	if (rc)
		return rc;

	return qed_spq_post(p_hwfn, p_ent, NULL);
}