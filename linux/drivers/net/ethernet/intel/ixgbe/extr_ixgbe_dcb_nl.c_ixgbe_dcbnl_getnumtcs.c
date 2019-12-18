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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pfc_tcs; int /*<<< orphan*/  pg_tcs; } ;
struct TYPE_4__ {TYPE_1__ num_tcs; } ;
struct ixgbe_adapter {int flags; TYPE_2__ dcb_cfg; } ;

/* Variables and functions */
#define  DCB_NUMTCS_ATTR_PFC 129 
#define  DCB_NUMTCS_ATTR_PG 128 
 int EINVAL ; 
 int IXGBE_FLAG_DCB_ENABLED ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_dcbnl_getnumtcs(struct net_device *netdev, int tcid, u8 *num)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	if (adapter->flags & IXGBE_FLAG_DCB_ENABLED) {
		switch (tcid) {
		case DCB_NUMTCS_ATTR_PG:
			*num = adapter->dcb_cfg.num_tcs.pg_tcs;
			break;
		case DCB_NUMTCS_ATTR_PFC:
			*num = adapter->dcb_cfg.num_tcs.pfc_tcs;
			break;
		default:
			return -EINVAL;
		}
	} else {
		return -EINVAL;
	}

	return 0;
}