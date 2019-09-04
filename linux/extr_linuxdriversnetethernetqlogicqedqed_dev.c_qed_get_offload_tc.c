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
struct TYPE_2__ {int /*<<< orphan*/  offload_tc; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_INIT_DEFAULT_TC ; 
 scalar_t__ qed_is_offload_tc_set (struct qed_hwfn*) ; 

__attribute__((used)) static u32 qed_get_offload_tc(struct qed_hwfn *p_hwfn)
{
	if (qed_is_offload_tc_set(p_hwfn))
		return p_hwfn->hw_info.offload_tc;

	return PQ_INIT_DEFAULT_TC;
}