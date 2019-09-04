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
struct TYPE_6__ {int /*<<< orphan*/  op_code; } ;
struct iscsi_spe_func_dstry {TYPE_3__ hdr; } ;
struct TYPE_5__ {struct iscsi_spe_func_dstry iscsi_destroy; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_spq_comp_cb {int dummy; } ;
struct qed_sp_init_data {int comp_mode; struct qed_spq_comp_cb* p_comp_data; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum spq_mode { ____Placeholder_spq_mode } spq_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_RAMROD_CMD_ID_DESTROY_FUNC ; 
 int /*<<< orphan*/  PROTOCOLID_ISCSI ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int /*<<< orphan*/  qed_spq_get_cid (struct qed_hwfn*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_spq_unregister_async_cb (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_sp_iscsi_func_stop(struct qed_hwfn *p_hwfn,
				  enum spq_mode comp_mode,
				  struct qed_spq_comp_cb *p_comp_addr)
{
	struct iscsi_spe_func_dstry *p_ramrod = NULL;
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	int rc = 0;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_DESTROY_FUNC,
				 PROTOCOLID_ISCSI, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.iscsi_destroy;
	p_ramrod->hdr.op_code = ISCSI_RAMROD_CMD_ID_DESTROY_FUNC;

	rc = qed_spq_post(p_hwfn, p_ent, NULL);

	qed_spq_unregister_async_cb(p_hwfn, PROTOCOLID_ISCSI);
	return rc;
}