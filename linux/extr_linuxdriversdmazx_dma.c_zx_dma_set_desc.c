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
struct zx_dma_phy {scalar_t__ base; } ;
struct zx_desc_hw {int /*<<< orphan*/  ctr; int /*<<< orphan*/  lli; int /*<<< orphan*/  src_x; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 scalar_t__ REG_ZX_CTRL ; 
 scalar_t__ REG_ZX_DST_ADDR ; 
 scalar_t__ REG_ZX_DST_ZY_STEP ; 
 scalar_t__ REG_ZX_LLI_ADDR ; 
 scalar_t__ REG_ZX_SRC_ADDR ; 
 scalar_t__ REG_ZX_SRC_ZY_STEP ; 
 scalar_t__ REG_ZX_TX_X_COUNT ; 
 scalar_t__ REG_ZX_TX_ZY_COUNT ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void zx_dma_set_desc(struct zx_dma_phy *phy, struct zx_desc_hw *hw)
{
	writel_relaxed(hw->saddr, phy->base + REG_ZX_SRC_ADDR);
	writel_relaxed(hw->daddr, phy->base + REG_ZX_DST_ADDR);
	writel_relaxed(hw->src_x, phy->base + REG_ZX_TX_X_COUNT);
	writel_relaxed(0, phy->base + REG_ZX_TX_ZY_COUNT);
	writel_relaxed(0, phy->base + REG_ZX_SRC_ZY_STEP);
	writel_relaxed(0, phy->base + REG_ZX_DST_ZY_STEP);
	writel_relaxed(hw->lli, phy->base + REG_ZX_LLI_ADDR);
	writel_relaxed(hw->ctr, phy->base + REG_ZX_CTRL);
}