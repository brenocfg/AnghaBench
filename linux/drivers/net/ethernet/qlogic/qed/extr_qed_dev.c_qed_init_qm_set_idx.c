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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ start_pq; } ;
struct qed_hwfn {TYPE_1__ qm_info; } ;

/* Variables and functions */
 scalar_t__* qed_init_qm_get_idx_from_flags (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_init_qm_set_idx(struct qed_hwfn *p_hwfn,
				u32 pq_flags, u16 pq_val)
{
	u16 *base_pq_idx = qed_init_qm_get_idx_from_flags(p_hwfn, pq_flags);

	*base_pq_idx = p_hwfn->qm_info.start_pq + pq_val;
}