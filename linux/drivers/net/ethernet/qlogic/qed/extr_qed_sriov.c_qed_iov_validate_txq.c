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
typedef  scalar_t__ u16 ;
struct qed_vf_info {scalar_t__ num_txqs; int /*<<< orphan*/  abs_vf_id; } ;
struct qed_hwfn {int dummy; } ;
typedef  enum qed_iov_validate_q_mode { ____Placeholder_qed_iov_validate_q_mode } qed_iov_validate_q_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int qed_iov_validate_queue_mode (struct qed_hwfn*,struct qed_vf_info*,scalar_t__,int,int) ; 

__attribute__((used)) static bool qed_iov_validate_txq(struct qed_hwfn *p_hwfn,
				 struct qed_vf_info *p_vf,
				 u16 tx_qid,
				 enum qed_iov_validate_q_mode mode)
{
	if (tx_qid >= p_vf->num_txqs) {
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "VF[0x%02x] - can't touch Tx queue[%04x]; Only 0x%04x are allocated\n",
			   p_vf->abs_vf_id, tx_qid, p_vf->num_txqs);
		return false;
	}

	return qed_iov_validate_queue_mode(p_hwfn, p_vf, tx_qid, mode, true);
}