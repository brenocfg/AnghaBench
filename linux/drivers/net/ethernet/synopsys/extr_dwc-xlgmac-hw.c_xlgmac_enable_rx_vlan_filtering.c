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
struct xlgmac_pdata {scalar_t__ mac_regs; } ;

/* Variables and functions */
 scalar_t__ MAC_PFR ; 
 int /*<<< orphan*/  MAC_PFR_VTFE_LEN ; 
 int /*<<< orphan*/  MAC_PFR_VTFE_POS ; 
 scalar_t__ MAC_VLANTR ; 
 int /*<<< orphan*/  MAC_VLANTR_ETV_LEN ; 
 int /*<<< orphan*/  MAC_VLANTR_ETV_POS ; 
 int /*<<< orphan*/  MAC_VLANTR_VL_LEN ; 
 int /*<<< orphan*/  MAC_VLANTR_VL_POS ; 
 int /*<<< orphan*/  MAC_VLANTR_VTHM_LEN ; 
 int /*<<< orphan*/  MAC_VLANTR_VTHM_POS ; 
 int /*<<< orphan*/  MAC_VLANTR_VTIM_LEN ; 
 int /*<<< orphan*/  MAC_VLANTR_VTIM_POS ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int xlgmac_enable_rx_vlan_filtering(struct xlgmac_pdata *pdata)
{
	u32 regval;

	regval = readl(pdata->mac_regs + MAC_PFR);
	/* Enable VLAN filtering */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_VTFE_POS,
				     MAC_PFR_VTFE_LEN, 1);
	writel(regval, pdata->mac_regs + MAC_PFR);

	regval = readl(pdata->mac_regs + MAC_VLANTR);
	/* Enable VLAN Hash Table filtering */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_VTHM_POS,
				     MAC_VLANTR_VTHM_LEN, 1);
	/* Disable VLAN tag inverse matching */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_VTIM_POS,
				     MAC_VLANTR_VTIM_LEN, 0);
	/* Only filter on the lower 12-bits of the VLAN tag */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_ETV_POS,
				     MAC_VLANTR_ETV_LEN, 1);
	/* In order for the VLAN Hash Table filtering to be effective,
	 * the VLAN tag identifier in the VLAN Tag Register must not
	 * be zero.  Set the VLAN tag identifier to "1" to enable the
	 * VLAN Hash Table filtering.  This implies that a VLAN tag of
	 * 1 will always pass filtering.
	 */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_VL_POS,
				     MAC_VLANTR_VL_LEN, 1);
	writel(regval, pdata->mac_regs + MAC_VLANTR);

	return 0;
}