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
struct qed_rdma_start_in_params {int dummy; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ QED_IS_IWARP_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int qed_iwarp_setup (struct qed_hwfn*,struct qed_rdma_start_in_params*) ; 
 int /*<<< orphan*/  qed_rdma_init_devinfo (struct qed_hwfn*,struct qed_rdma_start_in_params*) ; 
 int /*<<< orphan*/  qed_rdma_init_events (struct qed_hwfn*,struct qed_rdma_start_in_params*) ; 
 int qed_rdma_init_hw (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_rdma_init_port (struct qed_hwfn*) ; 
 int qed_rdma_reserve_lkey (struct qed_hwfn*) ; 
 int qed_rdma_start_fw (struct qed_hwfn*,struct qed_rdma_start_in_params*,struct qed_ptt*) ; 
 int qed_roce_setup (struct qed_hwfn*) ; 

__attribute__((used)) static int qed_rdma_setup(struct qed_hwfn *p_hwfn,
			  struct qed_ptt *p_ptt,
			  struct qed_rdma_start_in_params *params)
{
	int rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA setup\n");

	qed_rdma_init_devinfo(p_hwfn, params);
	qed_rdma_init_port(p_hwfn);
	qed_rdma_init_events(p_hwfn, params);

	rc = qed_rdma_reserve_lkey(p_hwfn);
	if (rc)
		return rc;

	rc = qed_rdma_init_hw(p_hwfn, p_ptt);
	if (rc)
		return rc;

	if (QED_IS_IWARP_PERSONALITY(p_hwfn)) {
		rc = qed_iwarp_setup(p_hwfn, params);
		if (rc)
			return rc;
	} else {
		rc = qed_roce_setup(p_hwfn);
		if (rc)
			return rc;
	}

	return qed_rdma_start_fw(p_hwfn, params, p_ptt);
}