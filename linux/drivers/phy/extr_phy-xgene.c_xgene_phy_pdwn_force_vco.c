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
struct xgene_phy_ctx {int /*<<< orphan*/  dev; } ;
typedef  enum cmu_type_t { ____Placeholder_cmu_type_t } cmu_type_t ;
typedef  enum clk_type_t { ____Placeholder_clk_type_t } clk_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMU_REG0 ; 
 int /*<<< orphan*/  CMU_REG0_PDOWN_MASK ; 
 int /*<<< orphan*/  CMU_REG16 ; 
 int /*<<< orphan*/  CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMU_REG32 ; 
 int /*<<< orphan*/  CMU_REG32_FORCE_VCOCAL_START_MASK ; 
 int PHY_CMU ; 
 int /*<<< orphan*/  cmu_rd (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmu_toggle1to0 (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmu_wr (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void xgene_phy_pdwn_force_vco(struct xgene_phy_ctx *ctx,
				     enum cmu_type_t cmu_type,
				     enum clk_type_t clk_type)
{
	u32 val;

	dev_dbg(ctx->dev, "Reset VCO and re-start again\n");
	if (cmu_type == PHY_CMU) {
		cmu_rd(ctx, cmu_type, CMU_REG16, &val);
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x7);
		cmu_wr(ctx, cmu_type, CMU_REG16, val);
	}

	cmu_toggle1to0(ctx, cmu_type, CMU_REG0, CMU_REG0_PDOWN_MASK);
	cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
		       CMU_REG32_FORCE_VCOCAL_START_MASK);
}