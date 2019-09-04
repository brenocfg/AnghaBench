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
struct bcm_iproc_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int CFG_EN_SHIFT ; 
 scalar_t__ CFG_OFFSET ; 
 int CFG_RESET_SHIFT ; 
 scalar_t__ IE_OFFSET ; 
 scalar_t__ IS_OFFSET ; 
 scalar_t__ M_FIFO_CTRL_OFFSET ; 
 int M_FIFO_RX_FLUSH_SHIFT ; 
 int M_FIFO_TX_FLUSH_SHIFT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int bcm_iproc_i2c_init(struct bcm_iproc_i2c_dev *iproc_i2c)
{
	u32 val;

	/* put controller in reset */
	val = readl(iproc_i2c->base + CFG_OFFSET);
	val |= 1 << CFG_RESET_SHIFT;
	val &= ~(1 << CFG_EN_SHIFT);
	writel(val, iproc_i2c->base + CFG_OFFSET);

	/* wait 100 usec per spec */
	udelay(100);

	/* bring controller out of reset */
	val &= ~(1 << CFG_RESET_SHIFT);
	writel(val, iproc_i2c->base + CFG_OFFSET);

	/* flush TX/RX FIFOs and set RX FIFO threshold to zero */
	val = (1 << M_FIFO_RX_FLUSH_SHIFT) | (1 << M_FIFO_TX_FLUSH_SHIFT);
	writel(val, iproc_i2c->base + M_FIFO_CTRL_OFFSET);
	/* disable all interrupts */
	writel(0, iproc_i2c->base + IE_OFFSET);

	/* clear all pending interrupts */
	writel(0xffffffff, iproc_i2c->base + IS_OFFSET);

	return 0;
}