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
struct mxic_nand_ctlr {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ HC_CFG ; 
 int HC_CFG_MAN_CS_ASSERT ; 
 int HC_CFG_MAN_CS_EN ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxic_nfc_cs_enable(struct mxic_nand_ctlr *nfc)
{
	writel(readl(nfc->regs + HC_CFG) | HC_CFG_MAN_CS_EN,
	       nfc->regs + HC_CFG);
	writel(HC_CFG_MAN_CS_ASSERT | readl(nfc->regs + HC_CFG),
	       nfc->regs + HC_CFG);
}