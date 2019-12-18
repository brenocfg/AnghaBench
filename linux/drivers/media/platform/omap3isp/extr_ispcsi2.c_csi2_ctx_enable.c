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
typedef  size_t u8 ;
typedef  unsigned int u32 ;
struct isp_device {int dummy; } ;
struct isp_csi2_device {int frame_skip; int output; int /*<<< orphan*/  regs1; struct isp_csi2_ctx_cfg* contexts; } ;
struct isp_csi2_ctx_cfg {size_t enabled; } ;

/* Variables and functions */
 int CSI2_OUTPUT_MEMORY ; 
 int /*<<< orphan*/  ISPCSI2_CTX_CTRL1 (size_t) ; 
 unsigned int ISPCSI2_CTX_CTRL1_COUNT_MASK ; 
 unsigned int ISPCSI2_CTX_CTRL1_COUNT_SHIFT ; 
 unsigned int ISPCSI2_CTX_CTRL1_COUNT_UNLOCK ; 
 unsigned int ISPCSI2_CTX_CTRL1_CTX_EN ; 
 unsigned int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_ctx_enable(struct isp_device *isp,
			    struct isp_csi2_device *csi2, u8 ctxnum, u8 enable)
{
	struct isp_csi2_ctx_cfg *ctx = &csi2->contexts[ctxnum];
	unsigned int skip = 0;
	u32 reg;

	reg = isp_reg_readl(isp, csi2->regs1, ISPCSI2_CTX_CTRL1(ctxnum));

	if (enable) {
		if (csi2->frame_skip)
			skip = csi2->frame_skip;
		else if (csi2->output & CSI2_OUTPUT_MEMORY)
			skip = 1;

		reg &= ~ISPCSI2_CTX_CTRL1_COUNT_MASK;
		reg |= ISPCSI2_CTX_CTRL1_COUNT_UNLOCK
		    |  (skip << ISPCSI2_CTX_CTRL1_COUNT_SHIFT)
		    |  ISPCSI2_CTX_CTRL1_CTX_EN;
	} else {
		reg &= ~ISPCSI2_CTX_CTRL1_CTX_EN;
	}

	isp_reg_writel(isp, reg, csi2->regs1, ISPCSI2_CTX_CTRL1(ctxnum));
	ctx->enabled = enable;
}