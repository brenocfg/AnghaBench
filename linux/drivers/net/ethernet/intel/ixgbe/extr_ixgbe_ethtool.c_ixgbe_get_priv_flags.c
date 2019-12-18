#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int flags2; } ;

/* Variables and functions */
 int IXGBE_FLAG2_RX_LEGACY ; 
 int IXGBE_FLAG2_VF_IPSEC_ENABLED ; 
 int /*<<< orphan*/  IXGBE_PRIV_FLAGS_LEGACY_RX ; 
 int /*<<< orphan*/  IXGBE_PRIV_FLAGS_VF_IPSEC_EN ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 ixgbe_get_priv_flags(struct net_device *netdev)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	u32 priv_flags = 0;

	if (adapter->flags2 & IXGBE_FLAG2_RX_LEGACY)
		priv_flags |= IXGBE_PRIV_FLAGS_LEGACY_RX;

	if (adapter->flags2 & IXGBE_FLAG2_VF_IPSEC_ENABLED)
		priv_flags |= IXGBE_PRIV_FLAGS_VF_IPSEC_EN;

	return priv_flags;
}