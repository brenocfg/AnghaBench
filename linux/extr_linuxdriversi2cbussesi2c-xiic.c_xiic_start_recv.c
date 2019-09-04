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
typedef  scalar_t__ u8 ;
struct xiic_i2c {int nmsgs; int tx_pos; struct i2c_msg* tx_msg; struct i2c_msg* rx_msg; } ;
struct i2c_msg {scalar_t__ len; int flags; } ;

/* Variables and functions */
 int I2C_M_NOSTART ; 
 scalar_t__ IIC_RX_FIFO_DEPTH ; 
 int /*<<< orphan*/  XIIC_DTR_REG_OFFSET ; 
 int XIIC_INTR_BNB_MASK ; 
 int XIIC_INTR_RX_FULL_MASK ; 
 int XIIC_INTR_TX_ERROR_MASK ; 
 int /*<<< orphan*/  XIIC_RFD_REG_OFFSET ; 
 int XIIC_TX_DYN_START_MASK ; 
 int XIIC_TX_DYN_STOP_MASK ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  xiic_irq_clr_en (struct xiic_i2c*,int) ; 
 int /*<<< orphan*/  xiic_setreg16 (struct xiic_i2c*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xiic_setreg8 (struct xiic_i2c*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xiic_start_recv(struct xiic_i2c *i2c)
{
	u8 rx_watermark;
	struct i2c_msg *msg = i2c->rx_msg = i2c->tx_msg;
	unsigned long flags;

	/* Clear and enable Rx full interrupt. */
	xiic_irq_clr_en(i2c, XIIC_INTR_RX_FULL_MASK | XIIC_INTR_TX_ERROR_MASK);

	/* we want to get all but last byte, because the TX_ERROR IRQ is used
	 * to inidicate error ACK on the address, and negative ack on the last
	 * received byte, so to not mix them receive all but last.
	 * In the case where there is only one byte to receive
	 * we can check if ERROR and RX full is set at the same time
	 */
	rx_watermark = msg->len;
	if (rx_watermark > IIC_RX_FIFO_DEPTH)
		rx_watermark = IIC_RX_FIFO_DEPTH;
	xiic_setreg8(i2c, XIIC_RFD_REG_OFFSET, rx_watermark - 1);

	local_irq_save(flags);
	if (!(msg->flags & I2C_M_NOSTART))
		/* write the address */
		xiic_setreg16(i2c, XIIC_DTR_REG_OFFSET,
			i2c_8bit_addr_from_msg(msg) | XIIC_TX_DYN_START_MASK);

	xiic_irq_clr_en(i2c, XIIC_INTR_BNB_MASK);

	xiic_setreg16(i2c, XIIC_DTR_REG_OFFSET,
		msg->len | ((i2c->nmsgs == 1) ? XIIC_TX_DYN_STOP_MASK : 0));
	local_irq_restore(flags);

	if (i2c->nmsgs == 1)
		/* very last, enable bus not busy as well */
		xiic_irq_clr_en(i2c, XIIC_INTR_BNB_MASK);

	/* the message is tx:ed */
	i2c->tx_pos = msg->len;
}