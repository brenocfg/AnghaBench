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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct vport_stop_ramrod_data {int /*<<< orphan*/  vport_id; } ;
struct TYPE_2__ {struct vport_stop_ramrod_data vport_stop; } ;
struct qed_spq_entry {TYPE_1__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RAMROD_VPORT_STOP ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_fw_vport (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int /*<<< orphan*/  qed_spq_get_cid (struct qed_hwfn*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 int qed_vf_pf_vport_stop (struct qed_hwfn*) ; 

int qed_sp_vport_stop(struct qed_hwfn *p_hwfn, u16 opaque_fid, u8 vport_id)
{
	struct vport_stop_ramrod_data *p_ramrod;
	struct qed_sp_init_data init_data;
	struct qed_spq_entry *p_ent;
	u8 abs_vport_id = 0;
	int rc;

	if (IS_VF(p_hwfn->cdev))
		return qed_vf_pf_vport_stop(p_hwfn);

	rc = qed_fw_vport(p_hwfn, vport_id, &abs_vport_id);
	if (rc)
		return rc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_VPORT_STOP,
				 PROTOCOLID_ETH, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.vport_stop;
	p_ramrod->vport_id = abs_vport_id;

	return qed_spq_post(p_hwfn, p_ent, NULL);
}