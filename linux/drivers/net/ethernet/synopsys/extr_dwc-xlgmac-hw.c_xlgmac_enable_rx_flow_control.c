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
 scalar_t__ MAC_RFCR ; 
 int /*<<< orphan*/  MAC_RFCR_RFE_LEN ; 
 int /*<<< orphan*/  MAC_RFCR_RFE_POS ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int xlgmac_enable_rx_flow_control(struct xlgmac_pdata *pdata)
{
	u32 regval;

	regval = readl(pdata->mac_regs + MAC_RFCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RFCR_RFE_POS,
				     MAC_RFCR_RFE_LEN, 1);
	writel(regval, pdata->mac_regs + MAC_RFCR);

	return 0;
}