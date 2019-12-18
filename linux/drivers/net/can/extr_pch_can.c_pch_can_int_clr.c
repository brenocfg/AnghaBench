#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pch_can_priv {TYPE_2__* regs; } ;
struct TYPE_4__ {TYPE_1__* ifregs; } ;
struct TYPE_3__ {int /*<<< orphan*/  creq; int /*<<< orphan*/  mcont; int /*<<< orphan*/  id1; int /*<<< orphan*/  id2; int /*<<< orphan*/  cmask; } ;

/* Variables and functions */
 int PCH_CMASK_ARB ; 
 int PCH_CMASK_CTRL ; 
 int PCH_CMASK_RDWR ; 
 int PCH_ID2_DIR ; 
 int PCH_IF_MCONT_INTPND ; 
 int PCH_IF_MCONT_NEWDAT ; 
 int PCH_IF_MCONT_TXRQXT ; 
 scalar_t__ PCH_RX_OBJ_END ; 
 scalar_t__ PCH_RX_OBJ_START ; 
 scalar_t__ PCH_TX_OBJ_END ; 
 scalar_t__ PCH_TX_OBJ_START ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_can_bit_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pch_can_bit_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pch_can_rw_msg_obj (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void pch_can_int_clr(struct pch_can_priv *priv, u32 mask)
{
	/* Clear interrupt for transmit object */
	if ((mask >= PCH_RX_OBJ_START) && (mask <= PCH_RX_OBJ_END)) {
		/* Setting CMASK for clearing the reception interrupts. */
		iowrite32(PCH_CMASK_RDWR | PCH_CMASK_CTRL | PCH_CMASK_ARB,
			  &priv->regs->ifregs[0].cmask);

		/* Clearing the Dir bit. */
		pch_can_bit_clear(&priv->regs->ifregs[0].id2, PCH_ID2_DIR);

		/* Clearing NewDat & IntPnd */
		pch_can_bit_clear(&priv->regs->ifregs[0].mcont,
				  PCH_IF_MCONT_NEWDAT | PCH_IF_MCONT_INTPND);

		pch_can_rw_msg_obj(&priv->regs->ifregs[0].creq, mask);
	} else if ((mask >= PCH_TX_OBJ_START) && (mask <= PCH_TX_OBJ_END)) {
		/*
		 * Setting CMASK for clearing interrupts for frame transmission.
		 */
		iowrite32(PCH_CMASK_RDWR | PCH_CMASK_CTRL | PCH_CMASK_ARB,
			  &priv->regs->ifregs[1].cmask);

		/* Resetting the ID registers. */
		pch_can_bit_set(&priv->regs->ifregs[1].id2,
			       PCH_ID2_DIR | (0x7ff << 2));
		iowrite32(0x0, &priv->regs->ifregs[1].id1);

		/* Claring NewDat, TxRqst & IntPnd */
		pch_can_bit_clear(&priv->regs->ifregs[1].mcont,
				  PCH_IF_MCONT_NEWDAT | PCH_IF_MCONT_INTPND |
				  PCH_IF_MCONT_TXRQXT);
		pch_can_rw_msg_obj(&priv->regs->ifregs[1].creq, mask);
	}
}