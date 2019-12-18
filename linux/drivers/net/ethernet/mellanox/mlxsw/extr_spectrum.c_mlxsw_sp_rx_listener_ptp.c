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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct mlxsw_sp {TYPE_1__* ptp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* receive ) (struct mlxsw_sp*,struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_rx_listener_ptp(struct sk_buff *skb, u8 local_port,
				     void *priv)
{
	struct mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp->ptp_ops->receive(mlxsw_sp, skb, local_port);
}