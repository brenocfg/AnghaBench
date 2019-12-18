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
struct net_device {int addr_len; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/ * san_addr; int /*<<< orphan*/ * perm_addr; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_ADDR_LEN ; 
#define  ixgbe_mac_82599EB 130 
#define  ixgbe_mac_X540 129 
#define  ixgbe_mac_X550 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbe_dcbnl_get_perm_hw_addr(struct net_device *netdev,
					 u8 *perm_addr)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	int i, j;

	memset(perm_addr, 0xff, MAX_ADDR_LEN);

	for (i = 0; i < netdev->addr_len; i++)
		perm_addr[i] = adapter->hw.mac.perm_addr[i];

	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
		for (j = 0; j < netdev->addr_len; j++, i++)
			perm_addr[i] = adapter->hw.mac.san_addr[j];
		break;
	default:
		break;
	}
}