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
typedef  size_t u16 ;
struct qed_vf_queue_cid {int b_is_tx; int /*<<< orphan*/  p_cid; } ;
struct qed_vf_info {TYPE_1__* vf_queues; } ;
struct qed_hwfn {int dummy; } ;
typedef  enum qed_iov_validate_q_mode { ____Placeholder_qed_iov_validate_q_mode } qed_iov_validate_q_mode ;
struct TYPE_2__ {struct qed_vf_queue_cid* cids; } ;

/* Variables and functions */
 int MAX_QUEUES_PER_QZONE ; 
 int QED_IOV_VALIDATE_Q_DISABLE ; 
 int QED_IOV_VALIDATE_Q_ENABLE ; 
 int QED_IOV_VALIDATE_Q_NA ; 

__attribute__((used)) static bool qed_iov_validate_queue_mode(struct qed_hwfn *p_hwfn,
					struct qed_vf_info *p_vf,
					u16 qid,
					enum qed_iov_validate_q_mode mode,
					bool b_is_tx)
{
	int i;

	if (mode == QED_IOV_VALIDATE_Q_NA)
		return true;

	for (i = 0; i < MAX_QUEUES_PER_QZONE; i++) {
		struct qed_vf_queue_cid *p_qcid;

		p_qcid = &p_vf->vf_queues[qid].cids[i];

		if (!p_qcid->p_cid)
			continue;

		if (p_qcid->b_is_tx != b_is_tx)
			continue;

		return mode == QED_IOV_VALIDATE_Q_ENABLE;
	}

	/* In case we haven't found any valid cid, then its disabled */
	return mode == QED_IOV_VALIDATE_Q_DISABLE;
}