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
struct ps2_gpio_data {unsigned char rx_byte; unsigned char rx_cnt; int /*<<< orphan*/  serio; int /*<<< orphan*/  dev; int /*<<< orphan*/  write_enable; int /*<<< orphan*/  gpio_data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PS2_CMD_RESEND ; 
#define  PS2_DATA_BIT0 138 
#define  PS2_DATA_BIT1 137 
#define  PS2_DATA_BIT2 136 
#define  PS2_DATA_BIT3 135 
#define  PS2_DATA_BIT4 134 
#define  PS2_DATA_BIT5 133 
#define  PS2_DATA_BIT6 132 
#define  PS2_DATA_BIT7 131 
 unsigned char PS2_DEV_RET_ACK ; 
 unsigned char PS2_DEV_RET_NACK ; 
#define  PS2_PARITY_BIT 130 
#define  PS2_START_BIT 129 
#define  PS2_STOP_BIT 128 
 int SERIO_PARITY ; 
 int /*<<< orphan*/  __ps2_gpio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int hweight8 (unsigned char) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,unsigned char,int) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long usecs_to_jiffies (int) ; 

__attribute__((used)) static irqreturn_t ps2_gpio_irq_rx(struct ps2_gpio_data *drvdata)
{
	unsigned char byte, cnt;
	int data;
	int rxflags = 0;
	static unsigned long old_jiffies;

	byte = drvdata->rx_byte;
	cnt = drvdata->rx_cnt;

	if (old_jiffies == 0)
		old_jiffies = jiffies;

	if ((jiffies - old_jiffies) > usecs_to_jiffies(100)) {
		dev_err(drvdata->dev,
			"RX: timeout, probably we missed an interrupt\n");
		goto err;
	}
	old_jiffies = jiffies;

	data = gpiod_get_value(drvdata->gpio_data);
	if (unlikely(data < 0)) {
		dev_err(drvdata->dev, "RX: failed to get data gpio val: %d\n",
			data);
		goto err;
	}

	switch (cnt) {
	case PS2_START_BIT:
		/* start bit should be low */
		if (unlikely(data)) {
			dev_err(drvdata->dev, "RX: start bit should be low\n");
			goto err;
		}
		break;
	case PS2_DATA_BIT0:
	case PS2_DATA_BIT1:
	case PS2_DATA_BIT2:
	case PS2_DATA_BIT3:
	case PS2_DATA_BIT4:
	case PS2_DATA_BIT5:
	case PS2_DATA_BIT6:
	case PS2_DATA_BIT7:
		/* processing data bits */
		if (data)
			byte |= (data << (cnt - 1));
		break;
	case PS2_PARITY_BIT:
		/* check odd parity */
		if (!((hweight8(byte) & 1) ^ data)) {
			rxflags |= SERIO_PARITY;
			dev_warn(drvdata->dev, "RX: parity error\n");
			if (!drvdata->write_enable)
				goto err;
		}

		/* Do not send spurious ACK's and NACK's when write fn is
		 * not provided.
		 */
		if (!drvdata->write_enable) {
			if (byte == PS2_DEV_RET_NACK)
				goto err;
			else if (byte == PS2_DEV_RET_ACK)
				break;
		}

		/* Let's send the data without waiting for the stop bit to be
		 * sent. It may happen that we miss the stop bit. When this
		 * happens we have no way to recover from this, certainly
		 * missing the parity bit would be recognized when processing
		 * the stop bit. When missing both, data is lost.
		 */
		serio_interrupt(drvdata->serio, byte, rxflags);
		dev_dbg(drvdata->dev, "RX: sending byte 0x%x\n", byte);
		break;
	case PS2_STOP_BIT:
		/* stop bit should be high */
		if (unlikely(!data)) {
			dev_err(drvdata->dev, "RX: stop bit should be high\n");
			goto err;
		}
		cnt = byte = 0;
		old_jiffies = 0;
		goto end; /* success */
	default:
		dev_err(drvdata->dev, "RX: got out of sync with the device\n");
		goto err;
	}

	cnt++;
	goto end; /* success */

err:
	cnt = byte = 0;
	old_jiffies = 0;
	__ps2_gpio_write(drvdata->serio, PS2_CMD_RESEND);
end:
	drvdata->rx_cnt = cnt;
	drvdata->rx_byte = byte;
	return IRQ_HANDLED;
}