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
struct xgbe_prv_data {int mdio_mmd; int /*<<< orphan*/  xpcs_lock; } ;

/* Variables and functions */
 int MII_ADDR_C45 ; 
 unsigned int PCS_V1_WINDOW_SELECT ; 
 int /*<<< orphan*/  XPCS32_IOWRITE (struct xgbe_prv_data*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xgbe_write_mmd_regs_v1(struct xgbe_prv_data *pdata, int prtad,
				   int mmd_reg, int mmd_data)
{
	unsigned int mmd_address;
	unsigned long flags;

	if (mmd_reg & MII_ADDR_C45)
		mmd_address = mmd_reg & ~MII_ADDR_C45;
	else
		mmd_address = (pdata->mdio_mmd << 16) | (mmd_reg & 0xffff);

	/* The PCS registers are accessed using mmio. The underlying APB3
	 * management interface uses indirect addressing to access the MMD
	 * register sets. This requires accessing of the PCS register in two
	 * phases, an address phase and a data phase.
	 *
	 * The mmio interface is based on 32-bit offsets and values. All
	 * register offsets must therefore be adjusted by left shifting the
	 * offset 2 bits and writing 32 bits of data.
	 */
	spin_lock_irqsave(&pdata->xpcs_lock, flags);
	XPCS32_IOWRITE(pdata, PCS_V1_WINDOW_SELECT, mmd_address >> 8);
	XPCS32_IOWRITE(pdata, (mmd_address & 0xff) << 2, mmd_data);
	spin_unlock_irqrestore(&pdata->xpcs_lock, flags);
}