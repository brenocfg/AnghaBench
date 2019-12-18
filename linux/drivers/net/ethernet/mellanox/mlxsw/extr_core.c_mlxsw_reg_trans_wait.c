#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_reg_trans {int err; int /*<<< orphan*/  bulk_list; int /*<<< orphan*/  emad_status; int /*<<< orphan*/  type; TYPE_2__* reg; int /*<<< orphan*/  tid; int /*<<< orphan*/  retries; int /*<<< orphan*/  timeout_dw; int /*<<< orphan*/  completion; struct mlxsw_core* core; } ;
struct mlxsw_core {TYPE_1__* bus_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_EMAD_MAX_RETRY ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct mlxsw_reg_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_reg_access_type_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_emad_op_tlv_status_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_id_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  priv_to_devlink (struct mlxsw_core*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  trace_devlink_hwerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_reg_trans_wait(struct mlxsw_reg_trans *trans)
{
	struct mlxsw_core *mlxsw_core = trans->core;
	int err;

	wait_for_completion(&trans->completion);
	cancel_delayed_work_sync(&trans->timeout_dw);
	err = trans->err;

	if (trans->retries)
		dev_warn(mlxsw_core->bus_info->dev, "EMAD retries (%d/%d) (tid=%llx)\n",
			 trans->retries, MLXSW_EMAD_MAX_RETRY, trans->tid);
	if (err) {
		dev_err(mlxsw_core->bus_info->dev, "EMAD reg access failed (tid=%llx,reg_id=%x(%s),type=%s,status=%x(%s))\n",
			trans->tid, trans->reg->id,
			mlxsw_reg_id_str(trans->reg->id),
			mlxsw_core_reg_access_type_str(trans->type),
			trans->emad_status,
			mlxsw_emad_op_tlv_status_str(trans->emad_status));
		trace_devlink_hwerr(priv_to_devlink(mlxsw_core),
				    trans->emad_status,
				    mlxsw_emad_op_tlv_status_str(trans->emad_status));
	}

	list_del(&trans->bulk_list);
	kfree_rcu(trans, rcu);
	return err;
}