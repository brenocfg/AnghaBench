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
struct sk_buff {int dummy; } ;
struct mlxsw_tx_info {int dummy; } ;
struct mlxsw_core {int /*<<< orphan*/  bus_priv; TYPE_1__* bus; } ;
struct TYPE_2__ {int (* skb_transmit ) (int /*<<< orphan*/ ,struct sk_buff*,struct mlxsw_tx_info const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct mlxsw_tx_info const*) ; 

int mlxsw_core_skb_transmit(struct mlxsw_core *mlxsw_core, struct sk_buff *skb,
			    const struct mlxsw_tx_info *tx_info)
{
	return mlxsw_core->bus->skb_transmit(mlxsw_core->bus_priv, skb,
					     tx_info);
}