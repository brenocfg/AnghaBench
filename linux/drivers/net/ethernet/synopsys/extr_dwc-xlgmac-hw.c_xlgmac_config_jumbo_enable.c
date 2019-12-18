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
struct xlgmac_pdata {scalar_t__ mac_regs; TYPE_1__* netdev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ MAC_RCR ; 
 int /*<<< orphan*/  MAC_RCR_JE_LEN ; 
 int /*<<< orphan*/  MAC_RCR_JE_POS ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ XLGMAC_STD_PACKET_MTU ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xlgmac_config_jumbo_enable(struct xlgmac_pdata *pdata)
{
	unsigned int val;
	u32 regval;

	val = (pdata->netdev->mtu > XLGMAC_STD_PACKET_MTU) ? 1 : 0;

	regval = readl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_JE_POS,
				     MAC_RCR_JE_LEN, val);
	writel(regval, pdata->mac_regs + MAC_RCR);
}