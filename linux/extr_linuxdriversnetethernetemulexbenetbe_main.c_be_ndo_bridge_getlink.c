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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct be_adapter {int /*<<< orphan*/  if_handle; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  BRIDGE_MODE_VEB ; 
 int /*<<< orphan*/  BRIDGE_MODE_VEPA ; 
 scalar_t__ PORT_FWD_TYPE_PASSTHRU ; 
 scalar_t__ PORT_FWD_TYPE_VEB ; 
 scalar_t__ PORT_FWD_TYPE_VEPA ; 
 int be_cmd_get_hsw_config (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int ndo_dflt_bridge_getlink (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_sriov_get_totalvfs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_ndo_bridge_getlink(struct sk_buff *skb, u32 pid, u32 seq,
				 struct net_device *dev, u32 filter_mask,
				 int nlflags)
{
	struct be_adapter *adapter = netdev_priv(dev);
	int status = 0;
	u8 hsw_mode;

	/* BE and Lancer chips support VEB mode only */
	if (BEx_chip(adapter) || lancer_chip(adapter)) {
		/* VEB is disabled in non-SR-IOV profiles on BE3/Lancer */
		if (!pci_sriov_get_totalvfs(adapter->pdev))
			return 0;
		hsw_mode = PORT_FWD_TYPE_VEB;
	} else {
		status = be_cmd_get_hsw_config(adapter, NULL, 0,
					       adapter->if_handle, &hsw_mode,
					       NULL);
		if (status)
			return 0;

		if (hsw_mode == PORT_FWD_TYPE_PASSTHRU)
			return 0;
	}

	return ndo_dflt_bridge_getlink(skb, pid, seq, dev,
				       hsw_mode == PORT_FWD_TYPE_VEPA ?
				       BRIDGE_MODE_VEPA : BRIDGE_MODE_VEB,
				       0, 0, nlflags, filter_mask, NULL);
}