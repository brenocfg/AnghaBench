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
struct qed_tunnel_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tunnel_config; } ;
struct TYPE_7__ {TYPE_2__ pf_update; } ;
struct qed_spq_entry {TYPE_3__ ramrod; } ;
struct qed_spq_comp_cb {int dummy; } ;
struct qed_sp_init_data {int comp_mode; struct qed_spq_comp_cb* p_comp_data; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_ptt {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_4__* cdev; TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum spq_mode { ____Placeholder_spq_mode } spq_mode ;
struct TYPE_8__ {int /*<<< orphan*/  tunnel; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_RAMROD_PF_UPDATE ; 
 int EINVAL ; 
 scalar_t__ IS_VF (TYPE_4__*) ; 
 int /*<<< orphan*/  PROTOCOLID_COMMON ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_set_hw_tunn_mode_port (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int /*<<< orphan*/  qed_spq_get_cid (struct qed_hwfn*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_tunn_set_pf_update_params (struct qed_hwfn*,struct qed_tunnel_info*,int /*<<< orphan*/ *) ; 
 int qed_vf_pf_tunnel_param_update (struct qed_hwfn*,struct qed_tunnel_info*) ; 

int qed_sp_pf_update_tunn_cfg(struct qed_hwfn *p_hwfn,
			      struct qed_ptt *p_ptt,
			      struct qed_tunnel_info *p_tunn,
			      enum spq_mode comp_mode,
			      struct qed_spq_comp_cb *p_comp_data)
{
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	int rc = -EINVAL;

	if (IS_VF(p_hwfn->cdev))
		return qed_vf_pf_tunnel_param_update(p_hwfn, p_tunn);

	if (!p_tunn)
		return -EINVAL;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_PF_UPDATE, PROTOCOLID_COMMON,
				 &init_data);
	if (rc)
		return rc;

	qed_tunn_set_pf_update_params(p_hwfn, p_tunn,
				      &p_ent->ramrod.pf_update.tunnel_config);

	rc = qed_spq_post(p_hwfn, p_ent, NULL);
	if (rc)
		return rc;

	qed_set_hw_tunn_mode_port(p_hwfn, p_ptt, &p_hwfn->cdev->tunnel);

	return rc;
}