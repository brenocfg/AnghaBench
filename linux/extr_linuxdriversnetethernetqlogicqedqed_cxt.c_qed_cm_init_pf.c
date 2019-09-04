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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_FLAGS_LB ; 
 int /*<<< orphan*/  STORE_RT_REG (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCM_REG_CON_PHY_Q3_RT_OFFSET ; 
 int /*<<< orphan*/  qed_get_cm_pq_idx (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_cm_init_pf(struct qed_hwfn *p_hwfn)
{
	/* XCM pure-LB queue */
	STORE_RT_REG(p_hwfn, XCM_REG_CON_PHY_Q3_RT_OFFSET,
		     qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_LB));
}