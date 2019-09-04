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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct omap_i2c_dev {int flags; int threshold; scalar_t__ rev; int b_hw; int latency; int speed; int /*<<< orphan*/ * set_mpu_wkup_lat; int /*<<< orphan*/  fifo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_I2C_BUF_REG ; 
 int OMAP_I2C_BUF_RXFIF_CLR ; 
 int OMAP_I2C_BUF_TXFIF_CLR ; 
 int OMAP_I2C_FLAG_NO_FIFO ; 
 scalar_t__ OMAP_I2C_REV_ON_3630 ; 
 int clamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_i2c_write_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap_i2c_resize_fifo(struct omap_i2c_dev *omap, u8 size, bool is_rx)
{
	u16		buf;

	if (omap->flags & OMAP_I2C_FLAG_NO_FIFO)
		return;

	/*
	 * Set up notification threshold based on message size. We're doing
	 * this to try and avoid draining feature as much as possible. Whenever
	 * we have big messages to transfer (bigger than our total fifo size)
	 * then we might use draining feature to transfer the remaining bytes.
	 */

	omap->threshold = clamp(size, (u8) 1, omap->fifo_size);

	buf = omap_i2c_read_reg(omap, OMAP_I2C_BUF_REG);

	if (is_rx) {
		/* Clear RX Threshold */
		buf &= ~(0x3f << 8);
		buf |= ((omap->threshold - 1) << 8) | OMAP_I2C_BUF_RXFIF_CLR;
	} else {
		/* Clear TX Threshold */
		buf &= ~0x3f;
		buf |= (omap->threshold - 1) | OMAP_I2C_BUF_TXFIF_CLR;
	}

	omap_i2c_write_reg(omap, OMAP_I2C_BUF_REG, buf);

	if (omap->rev < OMAP_I2C_REV_ON_3630)
		omap->b_hw = 1; /* Enable hardware fixes */

	/* calculate wakeup latency constraint for MPU */
	if (omap->set_mpu_wkup_lat != NULL)
		omap->latency = (1000000 * omap->threshold) /
			(1000 * omap->speed / 8);
}