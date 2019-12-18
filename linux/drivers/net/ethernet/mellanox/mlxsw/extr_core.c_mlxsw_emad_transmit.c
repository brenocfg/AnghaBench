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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct mlxsw_reg_trans {int /*<<< orphan*/  tx_info; int /*<<< orphan*/  active; int /*<<< orphan*/  tx_skb; } ;
struct mlxsw_core {TYPE_1__* driver; } ;
struct TYPE_2__ {scalar_t__ txhdr_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int mlxsw_core_skb_transmit (struct mlxsw_core*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_emad_trans_timeout_schedule (struct mlxsw_reg_trans*) ; 
 int /*<<< orphan*/  priv_to_devlink (struct mlxsw_core*) ; 
 struct sk_buff* skb_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_devlink_hwmsg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mlxsw_emad_transmit(struct mlxsw_core *mlxsw_core,
			       struct mlxsw_reg_trans *trans)
{
	struct sk_buff *skb;
	int err;

	skb = skb_copy(trans->tx_skb, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	trace_devlink_hwmsg(priv_to_devlink(mlxsw_core), false, 0,
			    skb->data + mlxsw_core->driver->txhdr_len,
			    skb->len - mlxsw_core->driver->txhdr_len);

	atomic_set(&trans->active, 1);
	err = mlxsw_core_skb_transmit(mlxsw_core, skb, &trans->tx_info);
	if (err) {
		dev_kfree_skb(skb);
		return err;
	}
	mlxsw_emad_trans_timeout_schedule(trans);
	return 0;
}