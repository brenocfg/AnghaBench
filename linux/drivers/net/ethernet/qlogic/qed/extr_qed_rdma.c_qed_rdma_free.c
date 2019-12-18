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
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  qed_cxt_free_proto_ilt (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_rdma_free_reserved_lkey (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_rdma_resc_free (struct qed_hwfn*) ; 

__attribute__((used)) static void qed_rdma_free(struct qed_hwfn *p_hwfn)
{
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Freeing RDMA\n");

	qed_rdma_free_reserved_lkey(p_hwfn);
	qed_cxt_free_proto_ilt(p_hwfn, p_hwfn->p_rdma_info->proto);
	qed_rdma_resc_free(p_hwfn);
}