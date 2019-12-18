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
typedef  int u16 ;
struct mlxsw_sp_ptp_state {int /*<<< orphan*/  unmatched_ht; int /*<<< orphan*/  ht_gc_dw; int /*<<< orphan*/  unmatched_lock; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct mlxsw_sp_ptp_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_MTPTPT_TRAP_ID_PTP0 ; 
 int /*<<< orphan*/  MLXSW_REG_MTPTPT_TRAP_ID_PTP1 ; 
 int /*<<< orphan*/  MLXSW_SP1_PTP_HT_GC_INTERVAL ; 
 int /*<<< orphan*/  MLXSW_SP_PTP_MESSAGE_TYPE_DELAY_REQ ; 
 int /*<<< orphan*/  MLXSW_SP_PTP_MESSAGE_TYPE_PDELAY_REQ ; 
 int /*<<< orphan*/  MLXSW_SP_PTP_MESSAGE_TYPE_PDELAY_RESP ; 
 int /*<<< orphan*/  MLXSW_SP_PTP_MESSAGE_TYPE_SYNC ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_ptp_state*) ; 
 struct mlxsw_sp_ptp_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_schedule_dw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_ht_gc ; 
 int mlxsw_sp1_ptp_set_fifo_clr_on_trap (struct mlxsw_sp*,int) ; 
 int mlxsw_sp1_ptp_shaper_params_set (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_unmatched_ht_params ; 
 int mlxsw_sp_ptp_mtptpt_set (struct mlxsw_sp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rhltable_destroy (int /*<<< orphan*/ *) ; 
 int rhltable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct mlxsw_sp_ptp_state *mlxsw_sp1_ptp_init(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_ptp_state *ptp_state;
	u16 message_type;
	int err;

	err = mlxsw_sp1_ptp_shaper_params_set(mlxsw_sp);
	if (err)
		return ERR_PTR(err);

	ptp_state = kzalloc(sizeof(*ptp_state), GFP_KERNEL);
	if (!ptp_state)
		return ERR_PTR(-ENOMEM);
	ptp_state->mlxsw_sp = mlxsw_sp;

	spin_lock_init(&ptp_state->unmatched_lock);

	err = rhltable_init(&ptp_state->unmatched_ht,
			    &mlxsw_sp1_ptp_unmatched_ht_params);
	if (err)
		goto err_hashtable_init;

	/* Delive these message types as PTP0. */
	message_type = BIT(MLXSW_SP_PTP_MESSAGE_TYPE_SYNC) |
		       BIT(MLXSW_SP_PTP_MESSAGE_TYPE_DELAY_REQ) |
		       BIT(MLXSW_SP_PTP_MESSAGE_TYPE_PDELAY_REQ) |
		       BIT(MLXSW_SP_PTP_MESSAGE_TYPE_PDELAY_RESP);
	err = mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP0,
				      message_type);
	if (err)
		goto err_mtptpt_set;

	/* Everything else is PTP1. */
	message_type = ~message_type;
	err = mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP1,
				      message_type);
	if (err)
		goto err_mtptpt1_set;

	err = mlxsw_sp1_ptp_set_fifo_clr_on_trap(mlxsw_sp, true);
	if (err)
		goto err_fifo_clr;

	INIT_DELAYED_WORK(&ptp_state->ht_gc_dw, mlxsw_sp1_ptp_ht_gc);
	mlxsw_core_schedule_dw(&ptp_state->ht_gc_dw,
			       MLXSW_SP1_PTP_HT_GC_INTERVAL);
	return ptp_state;

err_fifo_clr:
	mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP1, 0);
err_mtptpt1_set:
	mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP0, 0);
err_mtptpt_set:
	rhltable_destroy(&ptp_state->unmatched_ht);
err_hashtable_init:
	kfree(ptp_state);
	return ERR_PTR(err);
}