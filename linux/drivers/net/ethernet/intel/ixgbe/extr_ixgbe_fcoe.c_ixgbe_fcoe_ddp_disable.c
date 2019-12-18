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
struct ixgbe_fcoe {int /*<<< orphan*/ * ddp_pool; } ;
struct ixgbe_adapter {TYPE_1__* netdev; struct ixgbe_fcoe fcoe; } ;
struct TYPE_2__ {scalar_t__ fcoe_ddp_xid; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_fcoe_ddp_disable(struct ixgbe_adapter *adapter)
{
	struct ixgbe_fcoe *fcoe = &adapter->fcoe;

	adapter->netdev->fcoe_ddp_xid = 0;

	if (!fcoe->ddp_pool)
		return;

	free_percpu(fcoe->ddp_pool);
	fcoe->ddp_pool = NULL;
}