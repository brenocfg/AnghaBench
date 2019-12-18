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
struct TYPE_2__ {int flags; } ;
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;TYPE_1__ devtype; int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int XCAN_2_FSR_FL_MASK ; 
 int XCAN_2_FSR_RI_MASK ; 
 int XCAN_FLAG_CANFD_2 ; 
 int XCAN_FLAG_RX_FIFO_MULTI ; 
 int XCAN_FSR_FL_MASK ; 
 int /*<<< orphan*/  XCAN_FSR_OFFSET ; 
 int XCAN_FSR_RI_MASK ; 
 int /*<<< orphan*/  XCAN_ICR_OFFSET ; 
 int /*<<< orphan*/  XCAN_ISR_OFFSET ; 
 int XCAN_IXR_RXNEMP_MASK ; 
 int /*<<< orphan*/  XCAN_IXR_RXOK_MASK ; 
 int XCAN_RXFIFO_OFFSET ; 
 int XCAN_RXMSG_2_FRAME_OFFSET (int) ; 
 int XCAN_RXMSG_FRAME_OFFSET (int) ; 
 int /*<<< orphan*/  stub1 (struct xcan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int stub3 (struct xcan_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xcan_rx_fifo_get_next_frame(struct xcan_priv *priv)
{
	int offset;

	if (priv->devtype.flags & XCAN_FLAG_RX_FIFO_MULTI) {
		u32 fsr, mask;

		/* clear RXOK before the is-empty check so that any newly
		 * received frame will reassert it without a race
		 */
		priv->write_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_RXOK_MASK);

		fsr = priv->read_reg(priv, XCAN_FSR_OFFSET);

		/* check if RX FIFO is empty */
		if (priv->devtype.flags & XCAN_FLAG_CANFD_2)
			mask = XCAN_2_FSR_FL_MASK;
		else
			mask = XCAN_FSR_FL_MASK;

		if (!(fsr & mask))
			return -ENOENT;

		if (priv->devtype.flags & XCAN_FLAG_CANFD_2)
			offset =
			  XCAN_RXMSG_2_FRAME_OFFSET(fsr & XCAN_2_FSR_RI_MASK);
		else
			offset =
			  XCAN_RXMSG_FRAME_OFFSET(fsr & XCAN_FSR_RI_MASK);

	} else {
		/* check if RX FIFO is empty */
		if (!(priv->read_reg(priv, XCAN_ISR_OFFSET) &
		      XCAN_IXR_RXNEMP_MASK))
			return -ENOENT;

		/* frames are read from a static offset */
		offset = XCAN_RXFIFO_OFFSET;
	}

	return offset;
}