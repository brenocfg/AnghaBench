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
typedef  unsigned int u32 ;
struct xlgmac_pdata {scalar_t__ mac_regs; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 scalar_t__ MAC_PFR ; 
 int /*<<< orphan*/  MAC_PFR_PM_LEN ; 
 int /*<<< orphan*/  MAC_PFR_PM_POS ; 
 unsigned int XLGMAC_GET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int XLGMAC_SET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_dbg (struct xlgmac_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int xlgmac_set_all_multicast_mode(struct xlgmac_pdata *pdata,
					 unsigned int enable)
{
	unsigned int val = enable ? 1 : 0;
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(readl(pdata->mac_regs + MAC_PFR),
				     MAC_PFR_PM_POS, MAC_PFR_PM_LEN);
	if (regval == val)
		return 0;

	netif_dbg(pdata, drv, pdata->netdev, "%s allmulti mode\n",
		  enable ? "entering" : "leaving");

	regval = readl(pdata->mac_regs + MAC_PFR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_PM_POS,
				     MAC_PFR_PM_LEN, val);
	writel(regval, pdata->mac_regs + MAC_PFR);

	return 0;
}