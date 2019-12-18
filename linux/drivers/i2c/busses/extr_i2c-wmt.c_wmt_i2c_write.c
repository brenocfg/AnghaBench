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
typedef  int u16 ;
struct wmt_i2c_dev {scalar_t__ mode; scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; } ;
struct i2c_msg {int flags; int len; int* buf; int addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int CR_CPU_RDY ; 
 int CR_ENABLE ; 
 int CR_TX_END ; 
 int CSR_RCV_ACK_MASK ; 
 int CSR_RCV_NOT_ACK ; 
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ I2C_MODE_STANDARD ; 
 int I2C_M_NOSTART ; 
 scalar_t__ REG_CDR ; 
 scalar_t__ REG_CR ; 
 scalar_t__ REG_CSR ; 
 scalar_t__ REG_TCR ; 
 int TCR_FAST_MODE ; 
 int TCR_MASTER_WRITE ; 
 int TCR_SLAVE_ADDR_MASK ; 
 int TCR_STANDARD_MODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct wmt_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wmt_check_status (struct wmt_i2c_dev*) ; 
 int wmt_i2c_wait_bus_not_busy (struct wmt_i2c_dev*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int wmt_i2c_write(struct i2c_adapter *adap, struct i2c_msg *pmsg,
			 int last)
{
	struct wmt_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	u16 val, tcr_val;
	int ret;
	unsigned long wait_result;
	int xfer_len = 0;

	if (!(pmsg->flags & I2C_M_NOSTART)) {
		ret = wmt_i2c_wait_bus_not_busy(i2c_dev);
		if (ret < 0)
			return ret;
	}

	if (pmsg->len == 0) {
		/*
		 * We still need to run through the while (..) once, so
		 * start at -1 and break out early from the loop
		 */
		xfer_len = -1;
		writew(0, i2c_dev->base + REG_CDR);
	} else {
		writew(pmsg->buf[0] & 0xFF, i2c_dev->base + REG_CDR);
	}

	if (!(pmsg->flags & I2C_M_NOSTART)) {
		val = readw(i2c_dev->base + REG_CR);
		val &= ~CR_TX_END;
		writew(val, i2c_dev->base + REG_CR);

		val = readw(i2c_dev->base + REG_CR);
		val |= CR_CPU_RDY;
		writew(val, i2c_dev->base + REG_CR);
	}

	reinit_completion(&i2c_dev->complete);

	if (i2c_dev->mode == I2C_MODE_STANDARD)
		tcr_val = TCR_STANDARD_MODE;
	else
		tcr_val = TCR_FAST_MODE;

	tcr_val |= (TCR_MASTER_WRITE | (pmsg->addr & TCR_SLAVE_ADDR_MASK));

	writew(tcr_val, i2c_dev->base + REG_TCR);

	if (pmsg->flags & I2C_M_NOSTART) {
		val = readw(i2c_dev->base + REG_CR);
		val |= CR_CPU_RDY;
		writew(val, i2c_dev->base + REG_CR);
	}

	while (xfer_len < pmsg->len) {
		wait_result = wait_for_completion_timeout(&i2c_dev->complete,
							msecs_to_jiffies(500));

		if (wait_result == 0)
			return -ETIMEDOUT;

		ret = wmt_check_status(i2c_dev);
		if (ret)
			return ret;

		xfer_len++;

		val = readw(i2c_dev->base + REG_CSR);
		if ((val & CSR_RCV_ACK_MASK) == CSR_RCV_NOT_ACK) {
			dev_dbg(i2c_dev->dev, "write RCV NACK error\n");
			return -EIO;
		}

		if (pmsg->len == 0) {
			val = CR_TX_END | CR_CPU_RDY | CR_ENABLE;
			writew(val, i2c_dev->base + REG_CR);
			break;
		}

		if (xfer_len == pmsg->len) {
			if (last != 1)
				writew(CR_ENABLE, i2c_dev->base + REG_CR);
		} else {
			writew(pmsg->buf[xfer_len] & 0xFF, i2c_dev->base +
								REG_CDR);
			writew(CR_CPU_RDY | CR_ENABLE, i2c_dev->base + REG_CR);
		}
	}

	return 0;
}