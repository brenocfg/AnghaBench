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
struct mlxsw_core {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ptp_transmitted ) (struct mlxsw_core*,struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlxsw_core*,struct sk_buff*,int /*<<< orphan*/ ) ; 

void mlxsw_core_ptp_transmitted(struct mlxsw_core *mlxsw_core,
				struct sk_buff *skb, u8 local_port)
{
	if (mlxsw_core->driver->ptp_transmitted)
		mlxsw_core->driver->ptp_transmitted(mlxsw_core, skb,
						    local_port);
}