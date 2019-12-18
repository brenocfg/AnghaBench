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
typedef  int u32 ;
struct xlgmac_pdata {scalar_t__ mac_regs; } ;

/* Variables and functions */
 scalar_t__ MAC_TCR ; 
 int /*<<< orphan*/  MAC_TCR_SS_LEN ; 
 int /*<<< orphan*/  MAC_TCR_SS_POS ; 
 int XLGMAC_GET_REG_BITS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XLGMAC_SET_REG_BITS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int xlgmac_set_xlgmii_100000_speed(struct xlgmac_pdata *pdata)
{
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(readl(pdata->mac_regs + MAC_TCR),
				     MAC_TCR_SS_POS, MAC_TCR_SS_LEN);
	if (regval == 0x3)
		return 0;

	regval = readl(pdata->mac_regs + MAC_TCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_TCR_SS_POS,
				     MAC_TCR_SS_LEN, 0x3);
	writel(regval, pdata->mac_regs + MAC_TCR);

	return 0;
}