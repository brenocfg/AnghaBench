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
struct pch_can_priv {TYPE_2__* regs; } ;
struct TYPE_4__ {TYPE_1__* ifregs; } ;
struct TYPE_3__ {int /*<<< orphan*/  creq; int /*<<< orphan*/  cmask; int /*<<< orphan*/  mask2; int /*<<< orphan*/  mask1; int /*<<< orphan*/  mcont; int /*<<< orphan*/  id2; int /*<<< orphan*/  id1; } ;

/* Variables and functions */
 int PCH_CMASK_ARB ; 
 int PCH_CMASK_CTRL ; 
 int PCH_CMASK_MASK ; 
 int PCH_CMASK_RDWR ; 
 int PCH_CMASK_RX_TX_GET ; 
 int PCH_ID2_DIR ; 
 int PCH_IF_MCONT_EOB ; 
 int PCH_IF_MCONT_UMASK ; 
 int PCH_MASK2_MDIR_MXTD ; 
 int PCH_RX_OBJ_END ; 
 int PCH_RX_OBJ_START ; 
 int PCH_TX_OBJ_END ; 
 int PCH_TX_OBJ_START ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_can_bit_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pch_can_bit_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pch_can_rw_msg_obj (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pch_can_config_rx_tx_buffers(struct pch_can_priv *priv)
{
	int i;

	for (i = PCH_RX_OBJ_START; i <= PCH_RX_OBJ_END; i++) {
		iowrite32(PCH_CMASK_RX_TX_GET, &priv->regs->ifregs[0].cmask);
		pch_can_rw_msg_obj(&priv->regs->ifregs[0].creq, i);

		iowrite32(0x0, &priv->regs->ifregs[0].id1);
		iowrite32(0x0, &priv->regs->ifregs[0].id2);

		pch_can_bit_set(&priv->regs->ifregs[0].mcont,
				PCH_IF_MCONT_UMASK);

		/* In case FIFO mode, Last EoB of Rx Obj must be 1 */
		if (i == PCH_RX_OBJ_END)
			pch_can_bit_set(&priv->regs->ifregs[0].mcont,
					PCH_IF_MCONT_EOB);
		else
			pch_can_bit_clear(&priv->regs->ifregs[0].mcont,
					  PCH_IF_MCONT_EOB);

		iowrite32(0, &priv->regs->ifregs[0].mask1);
		pch_can_bit_clear(&priv->regs->ifregs[0].mask2,
				  0x1fff | PCH_MASK2_MDIR_MXTD);

		/* Setting CMASK for writing */
		iowrite32(PCH_CMASK_RDWR | PCH_CMASK_MASK | PCH_CMASK_ARB |
			  PCH_CMASK_CTRL, &priv->regs->ifregs[0].cmask);

		pch_can_rw_msg_obj(&priv->regs->ifregs[0].creq, i);
	}

	for (i = PCH_TX_OBJ_START; i <= PCH_TX_OBJ_END; i++) {
		iowrite32(PCH_CMASK_RX_TX_GET, &priv->regs->ifregs[1].cmask);
		pch_can_rw_msg_obj(&priv->regs->ifregs[1].creq, i);

		/* Resetting DIR bit for reception */
		iowrite32(0x0, &priv->regs->ifregs[1].id1);
		iowrite32(PCH_ID2_DIR, &priv->regs->ifregs[1].id2);

		/* Setting EOB bit for transmitter */
		iowrite32(PCH_IF_MCONT_EOB | PCH_IF_MCONT_UMASK,
			  &priv->regs->ifregs[1].mcont);

		iowrite32(0, &priv->regs->ifregs[1].mask1);
		pch_can_bit_clear(&priv->regs->ifregs[1].mask2, 0x1fff);

		/* Setting CMASK for writing */
		iowrite32(PCH_CMASK_RDWR | PCH_CMASK_MASK | PCH_CMASK_ARB |
			  PCH_CMASK_CTRL, &priv->regs->ifregs[1].cmask);

		pch_can_rw_msg_obj(&priv->regs->ifregs[1].creq, i);
	}
}