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
typedef  int u32 ;
struct xgene_edac_mc_ctx {TYPE_1__* edac; } ;
struct TYPE_2__ {int mc_active_mask; int /*<<< orphan*/  mcba_map; int /*<<< orphan*/  mcbb_map; int /*<<< orphan*/  csw_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSW_CSWCR ; 
 unsigned int CSW_CSWCR_DUALMCB_MASK ; 
 int /*<<< orphan*/  MCBADDRMR ; 
 unsigned int MCBADDRMR_DUALMCU_MODE_MASK ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int xgene_edac_mc_is_active(struct xgene_edac_mc_ctx *ctx, int mc_idx)
{
	unsigned int reg;
	u32 mcu_mask;

	if (regmap_read(ctx->edac->csw_map, CSW_CSWCR, &reg))
		return 0;

	if (reg & CSW_CSWCR_DUALMCB_MASK) {
		/*
		 * Dual MCB active - Determine if all 4 active or just MCU0
		 * and MCU2 active
		 */
		if (regmap_read(ctx->edac->mcbb_map, MCBADDRMR, &reg))
			return 0;
		mcu_mask = (reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0xF : 0x5;
	} else {
		/*
		 * Single MCB active - Determine if MCU0/MCU1 or just MCU0
		 * active
		 */
		if (regmap_read(ctx->edac->mcba_map, MCBADDRMR, &reg))
			return 0;
		mcu_mask = (reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0x3 : 0x1;
	}

	/* Save active MC mask if hasn't set already */
	if (!ctx->edac->mc_active_mask)
		ctx->edac->mc_active_mask = mcu_mask;

	return (mcu_mask & (1 << mc_idx)) ? 1 : 0;
}