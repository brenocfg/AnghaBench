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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct skge_hw {scalar_t__ phy_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_IRQ_MSK ; 
 int /*<<< orphan*/  PHY_BCOM_INT_MASK ; 
 scalar_t__ SK_PHY_BCOM ; 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XM_GP_PORT ; 
 int XM_GP_RES_STAT ; 
 int /*<<< orphan*/  XM_HSM ; 
 int /*<<< orphan*/  XM_IMSK ; 
 int XM_IMSK_DISABLE ; 
 int XM_MD_FRF ; 
 int XM_MD_FTF ; 
 int /*<<< orphan*/  XM_MODE ; 
 int /*<<< orphan*/  XM_RX_CMD ; 
 int /*<<< orphan*/  XM_TX_CMD ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_outhash (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int xm_read32 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xm_write32 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void genesis_reset(struct skge_hw *hw, int port)
{
	static const u8 zero[8]  = { 0 };
	u32 reg;

	skge_write8(hw, SK_REG(port, GMAC_IRQ_MSK), 0);

	/* reset the statistics module */
	xm_write32(hw, port, XM_GP_PORT, XM_GP_RES_STAT);
	xm_write16(hw, port, XM_IMSK, XM_IMSK_DISABLE);
	xm_write32(hw, port, XM_MODE, 0);		/* clear Mode Reg */
	xm_write16(hw, port, XM_TX_CMD, 0);	/* reset TX CMD Reg */
	xm_write16(hw, port, XM_RX_CMD, 0);	/* reset RX CMD Reg */

	/* disable Broadcom PHY IRQ */
	if (hw->phy_type == SK_PHY_BCOM)
		xm_write16(hw, port, PHY_BCOM_INT_MASK, 0xffff);

	xm_outhash(hw, port, XM_HSM, zero);

	/* Flush TX and RX fifo */
	reg = xm_read32(hw, port, XM_MODE);
	xm_write32(hw, port, XM_MODE, reg | XM_MD_FTF);
	xm_write32(hw, port, XM_MODE, reg | XM_MD_FRF);
}