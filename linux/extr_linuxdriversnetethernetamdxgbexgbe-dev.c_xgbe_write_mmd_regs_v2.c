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
struct xgbe_prv_data {int mdio_mmd; unsigned int xpcs_window_mask; unsigned int xpcs_window; int /*<<< orphan*/  xpcs_lock; int /*<<< orphan*/  xpcs_window_sel_reg; } ;

/* Variables and functions */
 int MII_ADDR_C45 ; 
 int /*<<< orphan*/  XPCS16_IOWRITE (struct xgbe_prv_data*,unsigned int,int) ; 
 int /*<<< orphan*/  XPCS32_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xgbe_write_mmd_regs_v2(struct xgbe_prv_data *pdata, int prtad,
				   int mmd_reg, int mmd_data)
{
	unsigned long flags;
	unsigned int mmd_address, index, offset;

	if (mmd_reg & MII_ADDR_C45)
		mmd_address = mmd_reg & ~MII_ADDR_C45;
	else
		mmd_address = (pdata->mdio_mmd << 16) | (mmd_reg & 0xffff);

	/* The PCS registers are accessed using mmio. The underlying
	 * management interface uses indirect addressing to access the MMD
	 * register sets. This requires accessing of the PCS register in two
	 * phases, an address phase and a data phase.
	 *
	 * The mmio interface is based on 16-bit offsets and values. All
	 * register offsets must therefore be adjusted by left shifting the
	 * offset 1 bit and writing 16 bits of data.
	 */
	mmd_address <<= 1;
	index = mmd_address & ~pdata->xpcs_window_mask;
	offset = pdata->xpcs_window + (mmd_address & pdata->xpcs_window_mask);

	spin_lock_irqsave(&pdata->xpcs_lock, flags);
	XPCS32_IOWRITE(pdata, pdata->xpcs_window_sel_reg, index);
	XPCS16_IOWRITE(pdata, offset, mmd_data);
	spin_unlock_irqrestore(&pdata->xpcs_lock, flags);
}