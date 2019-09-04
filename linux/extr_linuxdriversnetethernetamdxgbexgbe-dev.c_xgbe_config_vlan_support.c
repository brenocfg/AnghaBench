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
struct xgbe_prv_data {TYPE_1__* netdev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSVL ; 
 int /*<<< orphan*/  MAC_VLANIR ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  VLTI ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgbe_disable_rx_vlan_filtering (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_disable_rx_vlan_stripping (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_rx_vlan_filtering (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_rx_vlan_stripping (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_update_vlan_hash_table (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_config_vlan_support(struct xgbe_prv_data *pdata)
{
	/* Indicate that VLAN Tx CTAGs come from context descriptors */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANIR, CSVL, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANIR, VLTI, 1);

	/* Set the current VLAN Hash Table register value */
	xgbe_update_vlan_hash_table(pdata);

	if (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
		xgbe_enable_rx_vlan_filtering(pdata);
	else
		xgbe_disable_rx_vlan_filtering(pdata);

	if (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		xgbe_enable_rx_vlan_stripping(pdata);
	else
		xgbe_disable_rx_vlan_stripping(pdata);
}