#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  terminate_params_addr; } ;
struct fcoe_conn_terminate_ramrod_params {TYPE_3__ terminate_ramrod_data; } ;
struct TYPE_5__ {struct fcoe_conn_terminate_ramrod_params fcoe_conn_terminate; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_spq_comp_cb {int dummy; } ;
struct qed_sp_init_data {int comp_mode; struct qed_spq_comp_cb* p_comp_data; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;
struct qed_fcoe_conn {int /*<<< orphan*/  terminate_params; int /*<<< orphan*/  icid; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum spq_mode { ____Placeholder_spq_mode } spq_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCOE_RAMROD_CMD_ID_TERMINATE_CONN ; 
 int /*<<< orphan*/  PROTOCOLID_FCOE ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_sp_fcoe_conn_destroy(struct qed_hwfn *p_hwfn,
			 struct qed_fcoe_conn *p_conn,
			 enum spq_mode comp_mode,
			 struct qed_spq_comp_cb *p_comp_addr)
{
	struct fcoe_conn_terminate_ramrod_params *p_ramrod = NULL;
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	int rc = 0;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 FCOE_RAMROD_CMD_ID_TERMINATE_CONN,
				 PROTOCOLID_FCOE, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.fcoe_conn_terminate;
	DMA_REGPAIR_LE(p_ramrod->terminate_ramrod_data.terminate_params_addr,
		       p_conn->terminate_params);

	return qed_spq_post(p_hwfn, p_ent, NULL);
}