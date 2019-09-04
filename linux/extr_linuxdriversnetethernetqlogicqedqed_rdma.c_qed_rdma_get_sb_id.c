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
typedef  scalar_t__ u32 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ FEAT_NUM (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_PF_L2_QUE ; 

__attribute__((used)) static u32 qed_rdma_get_sb_id(void *p_hwfn, u32 rel_sb_id)
{
	/* First sb id for RoCE is after all the l2 sb */
	return FEAT_NUM((struct qed_hwfn *)p_hwfn, QED_PF_L2_QUE) + rel_sb_id;
}