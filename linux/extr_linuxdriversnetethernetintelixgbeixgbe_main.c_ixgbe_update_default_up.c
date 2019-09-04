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
struct ixgbe_adapter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ixgbe_update_default_up(struct ixgbe_adapter *adapter)
{
#ifdef CONFIG_IXGBE_DCB
	struct net_device *netdev = adapter->netdev;
	struct dcb_app app = {
			      .selector = IEEE_8021QAZ_APP_SEL_ETHERTYPE,
			      .protocol = 0,
			     };
	u8 up = 0;

	if (adapter->dcbx_cap & DCB_CAP_DCBX_VER_IEEE)
		up = dcb_ieee_getapp_mask(netdev, &app);

	adapter->default_up = (up > 1) ? (ffs(up) - 1) : 0;
#endif
}