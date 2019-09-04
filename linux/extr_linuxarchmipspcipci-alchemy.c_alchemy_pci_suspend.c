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
struct alchemy_pci_context {int* pm; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PCI_REG_B2BBASE0_VID ; 
 scalar_t__ PCI_REG_B2BBASE1_SID ; 
 scalar_t__ PCI_REG_B2BMASK_CCH ; 
 scalar_t__ PCI_REG_CLASSREV ; 
 scalar_t__ PCI_REG_CMEM ; 
 scalar_t__ PCI_REG_CONFIG ; 
 scalar_t__ PCI_REG_ID ; 
 scalar_t__ PCI_REG_MBAR ; 
 scalar_t__ PCI_REG_MWBASE_REV_CCL ; 
 scalar_t__ PCI_REG_MWMASK_DEV ; 
 scalar_t__ PCI_REG_PARAM ; 
 scalar_t__ PCI_REG_TIMEOUT ; 
 struct alchemy_pci_context* __alchemy_pci_ctx ; 
 int __raw_readl (scalar_t__) ; 

__attribute__((used)) static int alchemy_pci_suspend(void)
{
	struct alchemy_pci_context *ctx = __alchemy_pci_ctx;
	if (!ctx)
		return 0;

	ctx->pm[0]  = __raw_readl(ctx->regs + PCI_REG_CMEM);
	ctx->pm[1]  = __raw_readl(ctx->regs + PCI_REG_CONFIG) & 0x0009ffff;
	ctx->pm[2]  = __raw_readl(ctx->regs + PCI_REG_B2BMASK_CCH);
	ctx->pm[3]  = __raw_readl(ctx->regs + PCI_REG_B2BBASE0_VID);
	ctx->pm[4]  = __raw_readl(ctx->regs + PCI_REG_B2BBASE1_SID);
	ctx->pm[5]  = __raw_readl(ctx->regs + PCI_REG_MWMASK_DEV);
	ctx->pm[6]  = __raw_readl(ctx->regs + PCI_REG_MWBASE_REV_CCL);
	ctx->pm[7]  = __raw_readl(ctx->regs + PCI_REG_ID);
	ctx->pm[8]  = __raw_readl(ctx->regs + PCI_REG_CLASSREV);
	ctx->pm[9]  = __raw_readl(ctx->regs + PCI_REG_PARAM);
	ctx->pm[10] = __raw_readl(ctx->regs + PCI_REG_MBAR);
	ctx->pm[11] = __raw_readl(ctx->regs + PCI_REG_TIMEOUT);

	return 0;
}