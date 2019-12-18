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
typedef  int /*<<< orphan*/  u32 ;
struct xlgmac_pdata {TYPE_1__* netdev; scalar_t__ mac_regs; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 scalar_t__ MAC_VLANIR ; 
 int /*<<< orphan*/  MAC_VLANIR_CSVL_LEN ; 
 int /*<<< orphan*/  MAC_VLANIR_CSVL_POS ; 
 int /*<<< orphan*/  MAC_VLANIR_VLTI_LEN ; 
 int /*<<< orphan*/  MAC_VLANIR_VLTI_POS ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xlgmac_disable_rx_vlan_filtering (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_disable_rx_vlan_stripping (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_enable_rx_vlan_filtering (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_enable_rx_vlan_stripping (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_update_vlan_hash_table (struct xlgmac_pdata*) ; 

__attribute__((used)) static void xlgmac_config_vlan_support(struct xlgmac_pdata *pdata)
{
	u32 regval;

	regval = readl(pdata->mac_regs + MAC_VLANIR);
	/* Indicate that VLAN Tx CTAGs come from context descriptors */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANIR_CSVL_POS,
				     MAC_VLANIR_CSVL_LEN, 0);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANIR_VLTI_POS,
				     MAC_VLANIR_VLTI_LEN, 1);
	writel(regval, pdata->mac_regs + MAC_VLANIR);

	/* Set the current VLAN Hash Table register value */
	xlgmac_update_vlan_hash_table(pdata);

	if (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
		xlgmac_enable_rx_vlan_filtering(pdata);
	else
		xlgmac_disable_rx_vlan_filtering(pdata);

	if (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		xlgmac_enable_rx_vlan_stripping(pdata);
	else
		xlgmac_disable_rx_vlan_stripping(pdata);
}