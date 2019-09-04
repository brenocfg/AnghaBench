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
struct s3c24xx_i2c {int quirks; int /*<<< orphan*/  state; scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int QUIRK_HDMIPHY ; 
 scalar_t__ S3C2410_IICSTAT ; 
 unsigned long S3C2410_IICSTAT_START ; 
 unsigned long S3C2410_IICSTAT_TXRXEN ; 
 int /*<<< orphan*/  STATE_STOP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c24xx_i2c_disable_irq (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_master_complete (struct s3c24xx_i2c*,int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void s3c24xx_i2c_stop(struct s3c24xx_i2c *i2c, int ret)
{
	unsigned long iicstat = readl(i2c->regs + S3C2410_IICSTAT);

	dev_dbg(i2c->dev, "STOP\n");

	/*
	 * The datasheet says that the STOP sequence should be:
	 *  1) I2CSTAT.5 = 0	- Clear BUSY (or 'generate STOP')
	 *  2) I2CCON.4 = 0	- Clear IRQPEND
	 *  3) Wait until the stop condition takes effect.
	 *  4*) I2CSTAT.4 = 0	- Clear TXRXEN
	 *
	 * Where, step "4*" is only for buses with the "HDMIPHY" quirk.
	 *
	 * However, after much experimentation, it appears that:
	 * a) normal buses automatically clear BUSY and transition from
	 *    Master->Slave when they complete generating a STOP condition.
	 *    Therefore, step (3) can be done in doxfer() by polling I2CCON.4
	 *    after starting the STOP generation here.
	 * b) HDMIPHY bus does neither, so there is no way to do step 3.
	 *    There is no indication when this bus has finished generating
	 *    STOP.
	 *
	 * In fact, we have found that as soon as the IRQPEND bit is cleared in
	 * step 2, the HDMIPHY bus generates the STOP condition, and then
	 * immediately starts transferring another data byte, even though the
	 * bus is supposedly stopped.  This is presumably because the bus is
	 * still in "Master" mode, and its BUSY bit is still set.
	 *
	 * To avoid these extra post-STOP transactions on HDMI phy devices, we
	 * just disable Serial Output on the bus (I2CSTAT.4 = 0) directly,
	 * instead of first generating a proper STOP condition.  This should
	 * float SDA & SCK terminating the transfer.  Subsequent transfers
	 *  start with a proper START condition, and proceed normally.
	 *
	 * The HDMIPHY bus is an internal bus that always has exactly two
	 * devices, the host as Master and the HDMIPHY device as the slave.
	 * Skipping the STOP condition has been tested on this bus and works.
	 */
	if (i2c->quirks & QUIRK_HDMIPHY) {
		/* Stop driving the I2C pins */
		iicstat &= ~S3C2410_IICSTAT_TXRXEN;
	} else {
		/* stop the transfer */
		iicstat &= ~S3C2410_IICSTAT_START;
	}
	writel(iicstat, i2c->regs + S3C2410_IICSTAT);

	i2c->state = STATE_STOP;

	s3c24xx_i2c_master_complete(i2c, ret);
	s3c24xx_i2c_disable_irq(i2c);
}