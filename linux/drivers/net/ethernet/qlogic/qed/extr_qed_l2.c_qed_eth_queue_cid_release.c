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
struct qed_queue_cid {int vf_legacy; scalar_t__ vfid; int /*<<< orphan*/  cid; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int QED_QCID_LEGACY_VF_CID ; 
 scalar_t__ QED_QUEUE_CID_SELF ; 
 int /*<<< orphan*/  _qed_cxt_release_cid (struct qed_hwfn*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qed_eth_queue_qid_usage_del (struct qed_hwfn*,struct qed_queue_cid*) ; 
 int /*<<< orphan*/  vfree (struct qed_queue_cid*) ; 

void qed_eth_queue_cid_release(struct qed_hwfn *p_hwfn,
			       struct qed_queue_cid *p_cid)
{
	bool b_legacy_vf = !!(p_cid->vf_legacy & QED_QCID_LEGACY_VF_CID);

	if (IS_PF(p_hwfn->cdev) && !b_legacy_vf)
		_qed_cxt_release_cid(p_hwfn, p_cid->cid, p_cid->vfid);

	/* For PF's VFs we maintain the index inside queue-zone in IOV */
	if (p_cid->vfid == QED_QUEUE_CID_SELF)
		qed_eth_queue_qid_usage_del(p_hwfn, p_cid);

	vfree(p_cid);
}