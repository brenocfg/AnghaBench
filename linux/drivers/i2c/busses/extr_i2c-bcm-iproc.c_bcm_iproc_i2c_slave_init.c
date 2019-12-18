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
struct bcm_iproc_i2c_dev {TYPE_1__* slave; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_OFFSET ; 
 int /*<<< orphan*/  CFG_RESET_SHIFT ; 
 int /*<<< orphan*/  IE_OFFSET ; 
 int /*<<< orphan*/  IE_S_RX_EVENT_SHIFT ; 
 int /*<<< orphan*/  IE_S_START_BUSY_SHIFT ; 
 int ISR_MASK_SLAVE ; 
 int /*<<< orphan*/  IS_OFFSET ; 
 int SLAVE_CLOCK_STRETCH_TIME ; 
 int /*<<< orphan*/  S_CFG_EN_NIC_SMB_ADDR3_SHIFT ; 
 int S_CFG_NIC_SMB_ADDR3_MASK ; 
 int S_CFG_NIC_SMB_ADDR3_SHIFT ; 
 int /*<<< orphan*/  S_CFG_SMBUS_ADDR_OFFSET ; 
 int /*<<< orphan*/  S_FIFO_CTRL_OFFSET ; 
 int /*<<< orphan*/  S_FIFO_RX_FLUSH_SHIFT ; 
 int /*<<< orphan*/  S_FIFO_TX_FLUSH_SHIFT ; 
 int /*<<< orphan*/  TIM_CFG_OFFSET ; 
 int TIM_RAND_SLAVE_STRETCH_MASK ; 
 int TIM_RAND_SLAVE_STRETCH_SHIFT ; 
 int iproc_i2c_rd_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_i2c_wr_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bcm_iproc_i2c_slave_init(
	struct bcm_iproc_i2c_dev *iproc_i2c, bool need_reset)
{
	u32 val;

	if (need_reset) {
		/* put controller in reset */
		val = iproc_i2c_rd_reg(iproc_i2c, CFG_OFFSET);
		val |= BIT(CFG_RESET_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);

		/* wait 100 usec per spec */
		udelay(100);

		/* bring controller out of reset */
		val &= ~(BIT(CFG_RESET_SHIFT));
		iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);
	}

	/* flush TX/RX FIFOs */
	val = (BIT(S_FIFO_RX_FLUSH_SHIFT) | BIT(S_FIFO_TX_FLUSH_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, S_FIFO_CTRL_OFFSET, val);

	/* Maximum slave stretch time */
	val = iproc_i2c_rd_reg(iproc_i2c, TIM_CFG_OFFSET);
	val &= ~(TIM_RAND_SLAVE_STRETCH_MASK << TIM_RAND_SLAVE_STRETCH_SHIFT);
	val |= (SLAVE_CLOCK_STRETCH_TIME << TIM_RAND_SLAVE_STRETCH_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, TIM_CFG_OFFSET, val);

	/* Configure the slave address */
	val = iproc_i2c_rd_reg(iproc_i2c, S_CFG_SMBUS_ADDR_OFFSET);
	val |= BIT(S_CFG_EN_NIC_SMB_ADDR3_SHIFT);
	val &= ~(S_CFG_NIC_SMB_ADDR3_MASK << S_CFG_NIC_SMB_ADDR3_SHIFT);
	val |= (iproc_i2c->slave->addr << S_CFG_NIC_SMB_ADDR3_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, S_CFG_SMBUS_ADDR_OFFSET, val);

	/* clear all pending slave interrupts */
	iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, ISR_MASK_SLAVE);

	/* Enable interrupt register to indicate a valid byte in receive fifo */
	val = BIT(IE_S_RX_EVENT_SHIFT);
	/* Enable interrupt register for the Slave BUSY command */
	val |= BIT(IE_S_START_BUSY_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, val);
}