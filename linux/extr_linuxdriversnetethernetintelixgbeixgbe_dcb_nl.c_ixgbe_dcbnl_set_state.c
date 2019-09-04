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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pg_tcs; } ;
struct TYPE_4__ {TYPE_1__ num_tcs; } ;
struct ixgbe_adapter {int dcbx_cap; int flags; TYPE_2__ dcb_cfg; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_VER_CEE ; 
 int IXGBE_FLAG_DCB_ENABLED ; 
 int /*<<< orphan*/  ixgbe_setup_tc (struct net_device*,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 ixgbe_dcbnl_set_state(struct net_device *netdev, u8 state)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	/* Fail command if not in CEE mode */
	if (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		return 1;

	/* verify there is something to do, if not then exit */
	if (!state == !(adapter->flags & IXGBE_FLAG_DCB_ENABLED))
		return 0;

	return !!ixgbe_setup_tc(netdev,
				state ? adapter->dcb_cfg.num_tcs.pg_tcs : 0);
}