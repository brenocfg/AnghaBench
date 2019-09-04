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
typedef  int u32 ;
struct i2c_msg {int flags; int addr; } ;
struct dw_i2c_dev {size_t msg_write_idx; struct i2c_msg* msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_CLR_INTR ; 
 int /*<<< orphan*/  DW_IC_CON ; 
 int DW_IC_CON_10BITADDR_MASTER ; 
 int /*<<< orphan*/  DW_IC_ENABLE_STATUS ; 
 int /*<<< orphan*/  DW_IC_INTR_MASK ; 
 int DW_IC_INTR_MASTER_MASK ; 
 int /*<<< orphan*/  DW_IC_TAR ; 
 int DW_IC_TAR_10BITADDR_MASTER ; 
 int I2C_M_TEN ; 
 int /*<<< orphan*/  __i2c_dw_disable (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  __i2c_dw_enable (struct dw_i2c_dev*) ; 
 int dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_writel (struct dw_i2c_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_dw_disable_int (struct dw_i2c_dev*) ; 

__attribute__((used)) static void i2c_dw_xfer_init(struct dw_i2c_dev *dev)
{
	struct i2c_msg *msgs = dev->msgs;
	u32 ic_con, ic_tar = 0;

	/* Disable the adapter */
	__i2c_dw_disable(dev);

	/* If the slave address is ten bit address, enable 10BITADDR */
	ic_con = dw_readl(dev, DW_IC_CON);
	if (msgs[dev->msg_write_idx].flags & I2C_M_TEN) {
		ic_con |= DW_IC_CON_10BITADDR_MASTER;
		/*
		 * If I2C_DYNAMIC_TAR_UPDATE is set, the 10-bit addressing
		 * mode has to be enabled via bit 12 of IC_TAR register.
		 * We set it always as I2C_DYNAMIC_TAR_UPDATE can't be
		 * detected from registers.
		 */
		ic_tar = DW_IC_TAR_10BITADDR_MASTER;
	} else {
		ic_con &= ~DW_IC_CON_10BITADDR_MASTER;
	}

	dw_writel(dev, ic_con, DW_IC_CON);

	/*
	 * Set the slave (target) address and enable 10-bit addressing mode
	 * if applicable.
	 */
	dw_writel(dev, msgs[dev->msg_write_idx].addr | ic_tar, DW_IC_TAR);

	/* Enforce disabled interrupts (due to HW issues) */
	i2c_dw_disable_int(dev);

	/* Enable the adapter */
	__i2c_dw_enable(dev);

	/* Dummy read to avoid the register getting stuck on Bay Trail */
	dw_readl(dev, DW_IC_ENABLE_STATUS);

	/* Clear and enable interrupts */
	dw_readl(dev, DW_IC_CLR_INTR);
	dw_writel(dev, DW_IC_INTR_MASTER_MASK, DW_IC_INTR_MASK);
}