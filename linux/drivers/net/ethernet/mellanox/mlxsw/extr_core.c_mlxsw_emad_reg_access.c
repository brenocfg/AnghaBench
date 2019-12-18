#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int is_emad; int /*<<< orphan*/  local_port; } ;
struct mlxsw_reg_trans {unsigned long cb_priv; int type; struct sk_buff* tx_skb; int /*<<< orphan*/  bulk_list; int /*<<< orphan*/  list; TYPE_4__ tx_info; int /*<<< orphan*/  tid; struct mlxsw_reg_info const* reg; int /*<<< orphan*/ * cb; int /*<<< orphan*/  completion; int /*<<< orphan*/  timeout_dw; struct mlxsw_core* core; } ;
struct mlxsw_reg_info {int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  trans_list_lock; int /*<<< orphan*/  trans_list; } ;
struct mlxsw_core {TYPE_3__ emad; TYPE_2__* driver; TYPE_1__* bus_info; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  mlxsw_reg_trans_cb_t ;
typedef  enum mlxsw_core_reg_access_type { ____Placeholder_mlxsw_core_reg_access_type } mlxsw_core_reg_access_type ;
struct TYPE_6__ {int /*<<< orphan*/  (* txhdr_construct ) (struct sk_buff*,TYPE_4__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_PORT_CPU_PORT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_reg_access_type_str (int) ; 
 struct sk_buff* mlxsw_emad_alloc (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_emad_construct (struct sk_buff*,struct mlxsw_reg_info const*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_emad_trans_timeout_work ; 
 int mlxsw_emad_transmit (struct mlxsw_core*,struct mlxsw_reg_trans*) ; 
 int /*<<< orphan*/  mlxsw_reg_id_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,TYPE_4__*) ; 

__attribute__((used)) static int mlxsw_emad_reg_access(struct mlxsw_core *mlxsw_core,
				 const struct mlxsw_reg_info *reg,
				 char *payload,
				 enum mlxsw_core_reg_access_type type,
				 struct mlxsw_reg_trans *trans,
				 struct list_head *bulk_list,
				 mlxsw_reg_trans_cb_t *cb,
				 unsigned long cb_priv, u64 tid)
{
	struct sk_buff *skb;
	int err;

	dev_dbg(mlxsw_core->bus_info->dev, "EMAD reg access (tid=%llx,reg_id=%x(%s),type=%s)\n",
		tid, reg->id, mlxsw_reg_id_str(reg->id),
		mlxsw_core_reg_access_type_str(type));

	skb = mlxsw_emad_alloc(mlxsw_core, reg->len);
	if (!skb)
		return -ENOMEM;

	list_add_tail(&trans->bulk_list, bulk_list);
	trans->core = mlxsw_core;
	trans->tx_skb = skb;
	trans->tx_info.local_port = MLXSW_PORT_CPU_PORT;
	trans->tx_info.is_emad = true;
	INIT_DELAYED_WORK(&trans->timeout_dw, mlxsw_emad_trans_timeout_work);
	trans->tid = tid;
	init_completion(&trans->completion);
	trans->cb = cb;
	trans->cb_priv = cb_priv;
	trans->reg = reg;
	trans->type = type;

	mlxsw_emad_construct(skb, reg, payload, type, trans->tid);
	mlxsw_core->driver->txhdr_construct(skb, &trans->tx_info);

	spin_lock_bh(&mlxsw_core->emad.trans_list_lock);
	list_add_tail_rcu(&trans->list, &mlxsw_core->emad.trans_list);
	spin_unlock_bh(&mlxsw_core->emad.trans_list_lock);
	err = mlxsw_emad_transmit(mlxsw_core, trans);
	if (err)
		goto err_out;
	return 0;

err_out:
	spin_lock_bh(&mlxsw_core->emad.trans_list_lock);
	list_del_rcu(&trans->list);
	spin_unlock_bh(&mlxsw_core->emad.trans_list_lock);
	list_del(&trans->bulk_list);
	dev_kfree_skb(trans->tx_skb);
	return err;
}