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
struct mlxsw_sp1_ptp_unmatched {int /*<<< orphan*/  ht_node; } ;
struct mlxsw_sp {TYPE_1__* ptp_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  unmatched_ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp1_ptp_unmatched_ht_params ; 
 int rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp1_ptp_unmatched_remove(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp1_ptp_unmatched *unmatched)
{
	return rhltable_remove(&mlxsw_sp->ptp_state->unmatched_ht,
			       &unmatched->ht_node,
			       mlxsw_sp1_ptp_unmatched_ht_params);
}