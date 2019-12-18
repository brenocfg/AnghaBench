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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ hash_table_size; } ;
struct xlgmac_pdata {scalar_t__ mac_regs; TYPE_2__ hw_feat; TYPE_1__* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ MAC_PFR ; 
 int /*<<< orphan*/  MAC_PFR_HMC_LEN ; 
 int /*<<< orphan*/  MAC_PFR_HMC_POS ; 
 int /*<<< orphan*/  MAC_PFR_HPF_LEN ; 
 int /*<<< orphan*/  MAC_PFR_HPF_POS ; 
 int /*<<< orphan*/  MAC_PFR_HUC_LEN ; 
 int /*<<< orphan*/  MAC_PFR_HUC_POS ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xlgmac_set_mac_address (struct xlgmac_pdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_config_mac_address(struct xlgmac_pdata *pdata)
{
	u32 regval;

	xlgmac_set_mac_address(pdata, pdata->netdev->dev_addr);

	/* Filtering is done using perfect filtering and hash filtering */
	if (pdata->hw_feat.hash_table_size) {
		regval = readl(pdata->mac_regs + MAC_PFR);
		regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_HPF_POS,
					     MAC_PFR_HPF_LEN, 1);
		regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_HUC_POS,
					     MAC_PFR_HUC_LEN, 1);
		regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_HMC_POS,
					     MAC_PFR_HMC_LEN, 1);
		writel(regval, pdata->mac_regs + MAC_PFR);
	}
}