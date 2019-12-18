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
struct bcm_iproc_i2c_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_EN_SHIFT ; 
 int /*<<< orphan*/  CFG_OFFSET ; 
 int /*<<< orphan*/  CFG_RESET_SHIFT ; 
 int IE_M_ALL_INTERRUPT_MASK ; 
 int IE_M_ALL_INTERRUPT_SHIFT ; 
 int /*<<< orphan*/  IE_OFFSET ; 
 int /*<<< orphan*/  IS_OFFSET ; 
 int /*<<< orphan*/  M_FIFO_CTRL_OFFSET ; 
 int /*<<< orphan*/  M_FIFO_RX_FLUSH_SHIFT ; 
 int /*<<< orphan*/  M_FIFO_TX_FLUSH_SHIFT ; 
 int iproc_i2c_rd_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_i2c_wr_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bcm_iproc_i2c_init(struct bcm_iproc_i2c_dev *iproc_i2c)
{
	u32 val;

	/* put controller in reset */
	val = iproc_i2c_rd_reg(iproc_i2c, CFG_OFFSET);
	val |= BIT(CFG_RESET_SHIFT);
	val &= ~(BIT(CFG_EN_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);

	/* wait 100 usec per spec */
	udelay(100);

	/* bring controller out of reset */
	val &= ~(BIT(CFG_RESET_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);

	/* flush TX/RX FIFOs and set RX FIFO threshold to zero */
	val = (BIT(M_FIFO_RX_FLUSH_SHIFT) | BIT(M_FIFO_TX_FLUSH_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, M_FIFO_CTRL_OFFSET, val);
	/* disable all interrupts */
	val = iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
	val &= ~(IE_M_ALL_INTERRUPT_MASK <<
			IE_M_ALL_INTERRUPT_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, val);

	/* clear all pending interrupts */
	iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, 0xffffffff);

	return 0;
}