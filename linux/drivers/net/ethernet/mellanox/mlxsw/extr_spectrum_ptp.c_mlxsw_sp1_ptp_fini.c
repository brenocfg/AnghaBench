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
struct mlxsw_sp_ptp_state {int /*<<< orphan*/  unmatched_ht; int /*<<< orphan*/  ht_gc_dw; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_MTPTPT_TRAP_ID_PTP0 ; 
 int /*<<< orphan*/  MLXSW_REG_MTPTPT_TRAP_ID_PTP1 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_ptp_state*) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_mtpppc_set (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_set_fifo_clr_on_trap (struct mlxsw_sp*,int) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_unmatched_free_fn ; 
 int /*<<< orphan*/  mlxsw_sp_ptp_mtptpt_set (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhltable_free_and_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void mlxsw_sp1_ptp_fini(struct mlxsw_sp_ptp_state *ptp_state)
{
	struct mlxsw_sp *mlxsw_sp = ptp_state->mlxsw_sp;

	cancel_delayed_work_sync(&ptp_state->ht_gc_dw);
	mlxsw_sp1_ptp_mtpppc_set(mlxsw_sp, 0, 0);
	mlxsw_sp1_ptp_set_fifo_clr_on_trap(mlxsw_sp, false);
	mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP1, 0);
	mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP0, 0);
	rhltable_free_and_destroy(&ptp_state->unmatched_ht,
				  &mlxsw_sp1_ptp_unmatched_free_fn, NULL);
	kfree(ptp_state);
}