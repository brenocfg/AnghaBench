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
typedef  int u32 ;
struct exynos5_i2c {int /*<<< orphan*/  lock; scalar_t__ regs; TYPE_2__* msg; TYPE_1__* variant; } ;
struct TYPE_4__ {int flags; int len; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {scalar_t__ hw; int fifo_depth; } ;

/* Variables and functions */
 scalar_t__ HSI2C_ADDR ; 
 scalar_t__ HSI2C_AUTO_CONF ; 
 scalar_t__ HSI2C_CTL ; 
 scalar_t__ HSI2C_FIFO_CTL ; 
 scalar_t__ HSI2C_INT_ENABLE ; 
 int HSI2C_INT_I2C ; 
 int HSI2C_INT_I2C_TRANS ; 
 int HSI2C_INT_RX_ALMOSTFULL_EN ; 
 int HSI2C_INT_TRAILING_EN ; 
 int HSI2C_INT_TX_ALMOSTEMPTY_EN ; 
 int HSI2C_MASTER_RUN ; 
 int HSI2C_READ_WRITE ; 
 int HSI2C_RXCHON ; 
 int HSI2C_RXFIFO_EN ; 
 int HSI2C_RXFIFO_TRIGGER_LEVEL (unsigned short) ; 
 int HSI2C_SLV_ADDR_MAS (int /*<<< orphan*/ ) ; 
 int HSI2C_STOP_AFTER_TRANS ; 
 int HSI2C_TXCHON ; 
 int HSI2C_TXFIFO_EN ; 
 int HSI2C_TXFIFO_TRIGGER_LEVEL (unsigned short) ; 
 int I2C_M_RD ; 
 scalar_t__ I2C_TYPE_EXYNOS7 ; 
 int /*<<< orphan*/  exynos5_i2c_bus_check (struct exynos5_i2c*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void exynos5_i2c_message_start(struct exynos5_i2c *i2c, int stop)
{
	u32 i2c_ctl;
	u32 int_en = 0;
	u32 i2c_auto_conf = 0;
	u32 fifo_ctl;
	unsigned long flags;
	unsigned short trig_lvl;

	if (i2c->variant->hw == I2C_TYPE_EXYNOS7)
		int_en |= HSI2C_INT_I2C_TRANS;
	else
		int_en |= HSI2C_INT_I2C;

	i2c_ctl = readl(i2c->regs + HSI2C_CTL);
	i2c_ctl &= ~(HSI2C_TXCHON | HSI2C_RXCHON);
	fifo_ctl = HSI2C_RXFIFO_EN | HSI2C_TXFIFO_EN;

	if (i2c->msg->flags & I2C_M_RD) {
		i2c_ctl |= HSI2C_RXCHON;

		i2c_auto_conf |= HSI2C_READ_WRITE;

		trig_lvl = (i2c->msg->len > i2c->variant->fifo_depth) ?
			(i2c->variant->fifo_depth * 3 / 4) : i2c->msg->len;
		fifo_ctl |= HSI2C_RXFIFO_TRIGGER_LEVEL(trig_lvl);

		int_en |= (HSI2C_INT_RX_ALMOSTFULL_EN |
			HSI2C_INT_TRAILING_EN);
	} else {
		i2c_ctl |= HSI2C_TXCHON;

		trig_lvl = (i2c->msg->len > i2c->variant->fifo_depth) ?
			(i2c->variant->fifo_depth * 1 / 4) : i2c->msg->len;
		fifo_ctl |= HSI2C_TXFIFO_TRIGGER_LEVEL(trig_lvl);

		int_en |= HSI2C_INT_TX_ALMOSTEMPTY_EN;
	}

	writel(HSI2C_SLV_ADDR_MAS(i2c->msg->addr), i2c->regs + HSI2C_ADDR);

	writel(fifo_ctl, i2c->regs + HSI2C_FIFO_CTL);
	writel(i2c_ctl, i2c->regs + HSI2C_CTL);

	exynos5_i2c_bus_check(i2c);

	/*
	 * Enable interrupts before starting the transfer so that we don't
	 * miss any INT_I2C interrupts.
	 */
	spin_lock_irqsave(&i2c->lock, flags);
	writel(int_en, i2c->regs + HSI2C_INT_ENABLE);

	if (stop == 1)
		i2c_auto_conf |= HSI2C_STOP_AFTER_TRANS;
	i2c_auto_conf |= i2c->msg->len;
	i2c_auto_conf |= HSI2C_MASTER_RUN;
	writel(i2c_auto_conf, i2c->regs + HSI2C_AUTO_CONF);
	spin_unlock_irqrestore(&i2c->lock, flags);
}