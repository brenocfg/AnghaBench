#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct migor_ts_priv {int /*<<< orphan*/  input; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
#define  EVENT_PENDOWN 130 
#define  EVENT_PENUP 129 
#define  EVENT_REPEAT 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_recv (TYPE_1__*,int*,int) ; 
 int i2c_master_send (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t migor_ts_isr(int irq, void *dev_id)
{
	struct migor_ts_priv *priv = dev_id;
	unsigned short xpos, ypos;
	unsigned char event;
	u_int8_t buf[16];

	/*
	 * The touch screen controller chip is hooked up to the CPU
	 * using I2C and a single interrupt line. The interrupt line
	 * is pulled low whenever someone taps the screen. To deassert
	 * the interrupt line we need to acknowledge the interrupt by
	 * communicating with the controller over the slow i2c bus.
	 *
	 * Since I2C bus controller may sleep we are using threaded
	 * IRQ here.
	 */

	memset(buf, 0, sizeof(buf));

	/* Set Index 0 */
	buf[0] = 0;
	if (i2c_master_send(priv->client, buf, 1) != 1) {
		dev_err(&priv->client->dev, "Unable to write i2c index\n");
		goto out;
	}

	/* Now do Page Read */
	if (i2c_master_recv(priv->client, buf, sizeof(buf)) != sizeof(buf)) {
		dev_err(&priv->client->dev, "Unable to read i2c page\n");
		goto out;
	}

	ypos = ((buf[9] & 0x03) << 8 | buf[8]);
	xpos = ((buf[11] & 0x03) << 8 | buf[10]);
	event = buf[12];

	switch (event) {
	case EVENT_PENDOWN:
	case EVENT_REPEAT:
		input_report_key(priv->input, BTN_TOUCH, 1);
		input_report_abs(priv->input, ABS_X, ypos); /*X-Y swap*/
		input_report_abs(priv->input, ABS_Y, xpos);
		input_sync(priv->input);
		break;

	case EVENT_PENUP:
		input_report_key(priv->input, BTN_TOUCH, 0);
		input_sync(priv->input);
		break;
	}

 out:
	return IRQ_HANDLED;
}