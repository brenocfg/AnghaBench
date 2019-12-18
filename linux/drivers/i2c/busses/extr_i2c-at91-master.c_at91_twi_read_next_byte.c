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
struct at91_twi_dev {int buf_len; scalar_t__* buf; int recv_len_abort; int /*<<< orphan*/  dev; int /*<<< orphan*/  use_alt_cmd; TYPE_1__* msg; scalar_t__ base; } ;
struct TYPE_2__ {int flags; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_CR ; 
 scalar_t__ AT91_TWI_RHR ; 
 int /*<<< orphan*/  AT91_TWI_STOP ; 
 int I2C_M_RECV_LEN ; 
 scalar_t__ I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  at91_twi_read (struct at91_twi_dev*,scalar_t__) ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ readb_relaxed (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void at91_twi_read_next_byte(struct at91_twi_dev *dev)
{
	/*
	 * If we are in this case, it means there is garbage data in RHR, so
	 * delete them.
	 */
	if (!dev->buf_len) {
		at91_twi_read(dev, AT91_TWI_RHR);
		return;
	}

	/* 8bit read works with and without FIFO */
	*dev->buf = readb_relaxed(dev->base + AT91_TWI_RHR);
	--dev->buf_len;

	/* return if aborting, we only needed to read RHR to clear RXRDY*/
	if (dev->recv_len_abort)
		return;

	/* handle I2C_SMBUS_BLOCK_DATA */
	if (unlikely(dev->msg->flags & I2C_M_RECV_LEN)) {
		/* ensure length byte is a valid value */
		if (*dev->buf <= I2C_SMBUS_BLOCK_MAX && *dev->buf > 0) {
			dev->msg->flags &= ~I2C_M_RECV_LEN;
			dev->buf_len += *dev->buf;
			dev->msg->len = dev->buf_len + 1;
			dev_dbg(dev->dev, "received block length %zu\n",
					 dev->buf_len);
		} else {
			/* abort and send the stop by reading one more byte */
			dev->recv_len_abort = true;
			dev->buf_len = 1;
		}
	}

	/* send stop if second but last byte has been read */
	if (!dev->use_alt_cmd && dev->buf_len == 1)
		at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_STOP);

	dev_dbg(dev->dev, "read 0x%x, to go %zu\n", *dev->buf, dev->buf_len);

	++dev->buf;
}