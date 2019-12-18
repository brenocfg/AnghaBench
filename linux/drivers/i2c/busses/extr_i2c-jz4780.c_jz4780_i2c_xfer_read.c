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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct jz4780_i2c {unsigned char* rbuf; int rd_total_len; size_t cmd; int /*<<< orphan*/ * data_buf; TYPE_1__ adap; int /*<<< orphan*/ * cmd_buf; int /*<<< orphan*/  trans_waitq; int /*<<< orphan*/  lock; scalar_t__ rd_cmd_xfered; scalar_t__ rd_data_xfered; scalar_t__ is_write; scalar_t__ stop_hold; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  JZ4780_I2C_CTRL ; 
 unsigned short JZ4780_I2C_CTRL_STPHLD ; 
 int JZ4780_I2C_FIFO_LEN ; 
 int /*<<< orphan*/  JZ4780_I2C_INTM ; 
 unsigned short JZ4780_I2C_INTM_MRXFL ; 
 unsigned short JZ4780_I2C_INTM_MRXOF ; 
 unsigned short JZ4780_I2C_INTM_MTXABT ; 
 unsigned short JZ4780_I2C_INTM_MTXEMP ; 
 int /*<<< orphan*/  JZ4780_I2C_RXTL ; 
 int JZ4780_I2C_TIMEOUT ; 
 int /*<<< orphan*/  JZ4780_I2C_TXABRT ; 
 int /*<<< orphan*/  JZ4780_I2C_TXTL ; 
 unsigned short RX_LEVEL ; 
 unsigned short TX_LEVEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned short jz4780_i2c_readw (struct jz4780_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_i2c_txabrt (struct jz4780_i2c*,unsigned short) ; 
 int /*<<< orphan*/  jz4780_i2c_writew (struct jz4780_i2c*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int jz4780_i2c_xfer_read(struct jz4780_i2c *i2c,
				       unsigned char *buf, int len, int cnt,
				       int idx)
{
	int ret = 0;
	long timeout;
	int wait_time = JZ4780_I2C_TIMEOUT * (len + 5);
	unsigned short tmp;
	unsigned long flags;

	memset(buf, 0, len);

	spin_lock_irqsave(&i2c->lock, flags);

	i2c->stop_hold = 0;
	i2c->is_write = 0;
	i2c->rbuf = buf;
	i2c->rd_total_len = len;
	i2c->rd_data_xfered = 0;
	i2c->rd_cmd_xfered = 0;

	if (len <= JZ4780_I2C_FIFO_LEN)
		jz4780_i2c_writew(i2c, JZ4780_I2C_RXTL, len - 1);
	else
		jz4780_i2c_writew(i2c, JZ4780_I2C_RXTL, RX_LEVEL);

	jz4780_i2c_writew(i2c, JZ4780_I2C_TXTL, TX_LEVEL);

	jz4780_i2c_writew(i2c, JZ4780_I2C_INTM,
			  JZ4780_I2C_INTM_MRXFL | JZ4780_I2C_INTM_MTXEMP
			  | JZ4780_I2C_INTM_MTXABT | JZ4780_I2C_INTM_MRXOF);

	tmp = jz4780_i2c_readw(i2c, JZ4780_I2C_CTRL);
	tmp |= JZ4780_I2C_CTRL_STPHLD;
	jz4780_i2c_writew(i2c, JZ4780_I2C_CTRL, tmp);

	spin_unlock_irqrestore(&i2c->lock, flags);

	timeout = wait_for_completion_timeout(&i2c->trans_waitq,
					      msecs_to_jiffies(wait_time));

	if (!timeout) {
		dev_err(&i2c->adap.dev, "irq read timeout\n");
		dev_dbg(&i2c->adap.dev, "send cmd count:%d  %d\n",
			i2c->cmd, i2c->cmd_buf[i2c->cmd]);
		dev_dbg(&i2c->adap.dev, "receive data count:%d  %d\n",
			i2c->cmd, i2c->data_buf[i2c->cmd]);
		ret = -EIO;
	}

	tmp = jz4780_i2c_readw(i2c, JZ4780_I2C_TXABRT);
	if (tmp) {
		jz4780_i2c_txabrt(i2c, tmp);
		ret = -EIO;
	}

	return ret;
}