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
typedef  unsigned int u32 ;
struct xlgmac_pdata {TYPE_1__* netdev; scalar_t__ mac_regs; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 scalar_t__ MAC_PFR ; 
 int /*<<< orphan*/  MAC_PFR_PR_LEN ; 
 int /*<<< orphan*/  MAC_PFR_PR_POS ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 unsigned int XLGMAC_GET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int XLGMAC_SET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_dbg (struct xlgmac_pdata*,int /*<<< orphan*/ ,TYPE_1__*,char*,char*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  xlgmac_disable_rx_vlan_filtering (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_enable_rx_vlan_filtering (struct xlgmac_pdata*) ; 

__attribute__((used)) static int xlgmac_set_promiscuous_mode(struct xlgmac_pdata *pdata,
				       unsigned int enable)
{
	unsigned int val = enable ? 1 : 0;
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(readl(pdata->mac_regs + MAC_PFR),
				     MAC_PFR_PR_POS, MAC_PFR_PR_LEN);
	if (regval == val)
		return 0;

	netif_dbg(pdata, drv, pdata->netdev, "%s promiscuous mode\n",
		  enable ? "entering" : "leaving");

	regval = readl(pdata->mac_regs + MAC_PFR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_PR_POS,
				     MAC_PFR_PR_LEN, val);
	writel(regval, pdata->mac_regs + MAC_PFR);

	/* Hardware will still perform VLAN filtering in promiscuous mode */
	if (enable) {
		xlgmac_disable_rx_vlan_filtering(pdata);
	} else {
		if (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
			xlgmac_enable_rx_vlan_filtering(pdata);
	}

	return 0;
}