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
struct ps2_gpio_data {unsigned char tx_cnt; unsigned char tx_byte; int /*<<< orphan*/  serio; int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_done; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned char BIT (unsigned char) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  PS2_ACK_BIT 140 
#define  PS2_DATA_BIT0 139 
#define  PS2_DATA_BIT1 138 
#define  PS2_DATA_BIT2 137 
#define  PS2_DATA_BIT3 136 
#define  PS2_DATA_BIT4 135 
#define  PS2_DATA_BIT5 134 
#define  PS2_DATA_BIT6 133 
#define  PS2_DATA_BIT7 132 
 int /*<<< orphan*/  PS2_MODE_RX ; 
#define  PS2_PARITY_BIT 131 
#define  PS2_START_BIT 130 
#define  PS2_STOP_BIT 129 
#define  PS2_TX_TIMEOUT 128 
 int /*<<< orphan*/  __ps2_gpio_write (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int hweight8 (unsigned char) ; 
 unsigned long jiffies ; 
 unsigned long usecs_to_jiffies (int) ; 

__attribute__((used)) static irqreturn_t ps2_gpio_irq_tx(struct ps2_gpio_data *drvdata)
{
	unsigned char byte, cnt;
	int data;
	static unsigned long old_jiffies;

	cnt = drvdata->tx_cnt;
	byte = drvdata->tx_byte;

	if (old_jiffies == 0)
		old_jiffies = jiffies;

	if ((jiffies - old_jiffies) > usecs_to_jiffies(100)) {
		dev_err(drvdata->dev,
			"TX: timeout, probably we missed an interrupt\n");
		goto err;
	}
	old_jiffies = jiffies;

	switch (cnt) {
	case PS2_START_BIT:
		/* should never happen */
		dev_err(drvdata->dev,
			"TX: start bit should have been sent already\n");
		goto err;
	case PS2_DATA_BIT0:
	case PS2_DATA_BIT1:
	case PS2_DATA_BIT2:
	case PS2_DATA_BIT3:
	case PS2_DATA_BIT4:
	case PS2_DATA_BIT5:
	case PS2_DATA_BIT6:
	case PS2_DATA_BIT7:
		data = byte & BIT(cnt - 1);
		gpiod_set_value(drvdata->gpio_data, data);
		break;
	case PS2_PARITY_BIT:
		/* do odd parity */
		data = !(hweight8(byte) & 1);
		gpiod_set_value(drvdata->gpio_data, data);
		break;
	case PS2_STOP_BIT:
		/* release data line to generate stop bit */
		gpiod_direction_input(drvdata->gpio_data);
		break;
	case PS2_TX_TIMEOUT:
		/* Devices generate one extra clock pulse before sending the
		 * acknowledgment.
		 */
		break;
	case PS2_ACK_BIT:
		gpiod_direction_input(drvdata->gpio_data);
		data = gpiod_get_value(drvdata->gpio_data);
		if (data) {
			dev_warn(drvdata->dev, "TX: received NACK, retry\n");
			goto err;
		}

		drvdata->mode = PS2_MODE_RX;
		complete(&drvdata->tx_done);

		cnt = 1;
		old_jiffies = 0;
		goto end; /* success */
	default:
		/* Probably we missed the stop bit. Therefore we release data
		 * line and try again.
		 */
		gpiod_direction_input(drvdata->gpio_data);
		dev_err(drvdata->dev, "TX: got out of sync with the device\n");
		goto err;
	}

	cnt++;
	goto end; /* success */

err:
	cnt = 1;
	old_jiffies = 0;
	gpiod_direction_input(drvdata->gpio_data);
	__ps2_gpio_write(drvdata->serio, drvdata->tx_byte);
end:
	drvdata->tx_cnt = cnt;
	return IRQ_HANDLED;
}