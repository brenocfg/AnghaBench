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
struct mlxsw_reg_trans {int err; int /*<<< orphan*/  completion; int /*<<< orphan*/  list; int /*<<< orphan*/  tx_skb; struct mlxsw_core* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  trans_list_lock; } ;
struct mlxsw_core {TYPE_1__ emad; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_emad_trans_finish(struct mlxsw_reg_trans *trans, int err)
{
	struct mlxsw_core *mlxsw_core = trans->core;

	dev_kfree_skb(trans->tx_skb);
	spin_lock_bh(&mlxsw_core->emad.trans_list_lock);
	list_del_rcu(&trans->list);
	spin_unlock_bh(&mlxsw_core->emad.trans_list_lock);
	trans->err = err;
	complete(&trans->completion);
}