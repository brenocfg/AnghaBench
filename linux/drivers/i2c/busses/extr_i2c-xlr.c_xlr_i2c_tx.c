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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct xlr_i2c_private {int pos; scalar_t__ irq; int /*<<< orphan*/  iobase; TYPE_1__* cfg; struct i2c_adapter adap; } ;
struct TYPE_2__ {int cfg_extra; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int XLR_I2C_ACK_ERR ; 
 int /*<<< orphan*/  XLR_I2C_ADDR ; 
 int XLR_I2C_ARB_STARTERR ; 
 int /*<<< orphan*/  XLR_I2C_BYTECNT ; 
 int /*<<< orphan*/  XLR_I2C_CFG ; 
 int XLR_I2C_CFG_ADDR ; 
 int /*<<< orphan*/  XLR_I2C_DATAOUT ; 
 int /*<<< orphan*/  XLR_I2C_DEVADDR ; 
 int XLR_I2C_SDOEMPTY ; 
 int /*<<< orphan*/  XLR_I2C_STARTXFR ; 
 int XLR_I2C_STARTXFR_ND ; 
 int XLR_I2C_STARTXFR_WR ; 
 int /*<<< orphan*/  XLR_I2C_STATUS ; 
 int XLR_I2C_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  xlr_i2c_busy (struct xlr_i2c_private*,int) ; 
 int xlr_i2c_rdreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xlr_i2c_wait (struct xlr_i2c_private*,int) ; 
 int /*<<< orphan*/  xlr_i2c_wreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xlr_i2c_tx(struct xlr_i2c_private *priv,  u16 len,
	u8 *buf, u16 addr)
{
	struct i2c_adapter *adap = &priv->adap;
	unsigned long timeout, stoptime, checktime;
	u32 i2c_status;
	int pos, timedout;
	u8 offset;
	u32 xfer;

	offset = buf[0];
	xlr_i2c_wreg(priv->iobase, XLR_I2C_ADDR, offset);
	xlr_i2c_wreg(priv->iobase, XLR_I2C_DEVADDR, addr);
	xlr_i2c_wreg(priv->iobase, XLR_I2C_CFG,
			XLR_I2C_CFG_ADDR | priv->cfg->cfg_extra);

	timeout = msecs_to_jiffies(XLR_I2C_TIMEOUT);
	stoptime = jiffies + timeout;
	timedout = 0;

	if (len == 1) {
		xlr_i2c_wreg(priv->iobase, XLR_I2C_BYTECNT, len - 1);
		xfer = XLR_I2C_STARTXFR_ND;
		pos = 1;
	} else {
		xlr_i2c_wreg(priv->iobase, XLR_I2C_BYTECNT, len - 2);
		xlr_i2c_wreg(priv->iobase, XLR_I2C_DATAOUT, buf[1]);
		xfer = XLR_I2C_STARTXFR_WR;
		pos = 2;
	}

	priv->pos = pos;

retry:
	/* retry can only happen on the first byte */
	xlr_i2c_wreg(priv->iobase, XLR_I2C_STARTXFR, xfer);

	if (priv->irq > 0)
		return xlr_i2c_wait(priv, XLR_I2C_TIMEOUT * len);

	while (!timedout) {
		checktime = jiffies;
		i2c_status = xlr_i2c_rdreg(priv->iobase, XLR_I2C_STATUS);

		if ((i2c_status & XLR_I2C_SDOEMPTY) && pos < len) {
			xlr_i2c_wreg(priv->iobase, XLR_I2C_DATAOUT, buf[pos++]);

			/* reset timeout on successful xmit */
			stoptime = jiffies + timeout;
		}
		timedout = time_after(checktime, stoptime);

		if (i2c_status & XLR_I2C_ARB_STARTERR) {
			if (timedout)
				break;
			goto retry;
		}

		if (i2c_status & XLR_I2C_ACK_ERR)
			return -EIO;

		if (!xlr_i2c_busy(priv, i2c_status) && pos >= len)
			return 0;
	}
	dev_err(&adap->dev, "I2C transmit timeout\n");
	return -ETIMEDOUT;
}