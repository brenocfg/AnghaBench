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
struct st_i2c_client {int addr; int count; int /*<<< orphan*/  result; int /*<<< orphan*/  xfered; } ;
struct st_i2c_dev {scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; struct st_i2c_client client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ SSC_CLR ; 
 int SSC_CLR_NACK ; 
 int SSC_CLR_SSCARBL ; 
 scalar_t__ SSC_I2C ; 
 int /*<<< orphan*/  SSC_I2C_STOPG ; 
 scalar_t__ SSC_IEN ; 
 int SSC_IEN_ARBLEN ; 
 int SSC_IEN_STOPEN ; 
 scalar_t__ SSC_STA ; 
#define  SSC_STA_ARBL 132 
#define  SSC_STA_NACK 131 
#define  SSC_STA_REPSTRT 130 
#define  SSC_STA_STOP 129 
#define  SSC_STA_TE 128 
 int __fls (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  st_i2c_handle_read (struct st_i2c_dev*) ; 
 int /*<<< orphan*/  st_i2c_handle_write (struct st_i2c_dev*) ; 
 int /*<<< orphan*/  st_i2c_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t st_i2c_isr_thread(int irq, void *data)
{
	struct st_i2c_dev *i2c_dev = data;
	struct st_i2c_client *c = &i2c_dev->client;
	u32 sta, ien;
	int it;

	ien = readl_relaxed(i2c_dev->base + SSC_IEN);
	sta = readl_relaxed(i2c_dev->base + SSC_STA);

	/* Use __fls() to check error bits first */
	it = __fls(sta & ien);
	if (it < 0) {
		dev_dbg(i2c_dev->dev, "spurious it (sta=0x%04x, ien=0x%04x)\n",
				sta, ien);
		return IRQ_NONE;
	}

	switch (1 << it) {
	case SSC_STA_TE:
		if (c->addr & I2C_M_RD)
			st_i2c_handle_read(i2c_dev);
		else
			st_i2c_handle_write(i2c_dev);
		break;

	case SSC_STA_STOP:
	case SSC_STA_REPSTRT:
		writel_relaxed(0, i2c_dev->base + SSC_IEN);
		complete(&i2c_dev->complete);
		break;

	case SSC_STA_NACK:
		writel_relaxed(SSC_CLR_NACK, i2c_dev->base + SSC_CLR);

		/* Last received byte handled by NACK interrupt */
		if ((c->addr & I2C_M_RD) && (c->count == 1) && (c->xfered)) {
			st_i2c_handle_read(i2c_dev);
			break;
		}

		it = SSC_IEN_STOPEN | SSC_IEN_ARBLEN;
		writel_relaxed(it, i2c_dev->base + SSC_IEN);

		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
		c->result = -EIO;
		break;

	case SSC_STA_ARBL:
		writel_relaxed(SSC_CLR_SSCARBL, i2c_dev->base + SSC_CLR);

		it = SSC_IEN_STOPEN | SSC_IEN_ARBLEN;
		writel_relaxed(it, i2c_dev->base + SSC_IEN);

		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
		c->result = -EAGAIN;
		break;

	default:
		dev_err(i2c_dev->dev,
				"it %d unhandled (sta=0x%04x)\n", it, sta);
	}

	/*
	 * Read IEN register to ensure interrupt mask write is effective
	 * before re-enabling interrupt at GIC level, and thus avoid spurious
	 * interrupts.
	 */
	readl(i2c_dev->base + SSC_IEN);

	return IRQ_HANDLED;
}