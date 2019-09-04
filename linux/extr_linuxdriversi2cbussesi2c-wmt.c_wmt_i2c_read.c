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
typedef  size_t u32 ;
typedef  int u16 ;
struct wmt_i2c_dev {scalar_t__ mode; scalar_t__ base; int /*<<< orphan*/  complete; } ;
struct i2c_msg {int flags; int len; int addr; int* buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int CR_CPU_RDY ; 
 int CR_TX_END ; 
 int CR_TX_NEXT_NO_ACK ; 
 int ETIMEDOUT ; 
 scalar_t__ I2C_MODE_STANDARD ; 
 int I2C_M_NOSTART ; 
 scalar_t__ REG_CDR ; 
 scalar_t__ REG_CR ; 
 scalar_t__ REG_TCR ; 
 int TCR_FAST_MODE ; 
 int TCR_MASTER_READ ; 
 int TCR_SLAVE_ADDR_MASK ; 
 int TCR_STANDARD_MODE ; 
 struct wmt_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wmt_check_status (struct wmt_i2c_dev*) ; 
 int wmt_i2c_wait_bus_not_busy (struct wmt_i2c_dev*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int wmt_i2c_read(struct i2c_adapter *adap, struct i2c_msg *pmsg,
			int last)
{
	struct wmt_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	u16 val, tcr_val;
	int ret;
	unsigned long wait_result;
	u32 xfer_len = 0;

	if (!(pmsg->flags & I2C_M_NOSTART)) {
		ret = wmt_i2c_wait_bus_not_busy(i2c_dev);
		if (ret < 0)
			return ret;
	}

	val = readw(i2c_dev->base + REG_CR);
	val &= ~CR_TX_END;
	writew(val, i2c_dev->base + REG_CR);

	val = readw(i2c_dev->base + REG_CR);
	val &= ~CR_TX_NEXT_NO_ACK;
	writew(val, i2c_dev->base + REG_CR);

	if (!(pmsg->flags & I2C_M_NOSTART)) {
		val = readw(i2c_dev->base + REG_CR);
		val |= CR_CPU_RDY;
		writew(val, i2c_dev->base + REG_CR);
	}

	if (pmsg->len == 1) {
		val = readw(i2c_dev->base + REG_CR);
		val |= CR_TX_NEXT_NO_ACK;
		writew(val, i2c_dev->base + REG_CR);
	}

	reinit_completion(&i2c_dev->complete);

	if (i2c_dev->mode == I2C_MODE_STANDARD)
		tcr_val = TCR_STANDARD_MODE;
	else
		tcr_val = TCR_FAST_MODE;

	tcr_val |= TCR_MASTER_READ | (pmsg->addr & TCR_SLAVE_ADDR_MASK);

	writew(tcr_val, i2c_dev->base + REG_TCR);

	if (pmsg->flags & I2C_M_NOSTART) {
		val = readw(i2c_dev->base + REG_CR);
		val |= CR_CPU_RDY;
		writew(val, i2c_dev->base + REG_CR);
	}

	while (xfer_len < pmsg->len) {
		wait_result = wait_for_completion_timeout(&i2c_dev->complete,
							msecs_to_jiffies(500));

		if (!wait_result)
			return -ETIMEDOUT;

		ret = wmt_check_status(i2c_dev);
		if (ret)
			return ret;

		pmsg->buf[xfer_len] = readw(i2c_dev->base + REG_CDR) >> 8;
		xfer_len++;

		if (xfer_len == pmsg->len - 1) {
			val = readw(i2c_dev->base + REG_CR);
			val |= (CR_TX_NEXT_NO_ACK | CR_CPU_RDY);
			writew(val, i2c_dev->base + REG_CR);
		} else {
			val = readw(i2c_dev->base + REG_CR);
			val |= CR_CPU_RDY;
			writew(val, i2c_dev->base + REG_CR);
		}
	}

	return 0;
}