#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ brightness; } ;
struct tm2_touchkey_data {int num_keycodes; TYPE_2__ led_dev; TYPE_1__* variant; int /*<<< orphan*/  input_dev; int /*<<< orphan*/ * keycodes; TYPE_3__* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ fixed_regulator; int /*<<< orphan*/  keycode_reg; scalar_t__ no_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ LED_OFF ; 
 int TM2_TOUCHKEY_BIT_KEYCODE ; 
 int TM2_TOUCHKEY_BIT_PRESS_EV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte (TYPE_3__*) ; 
 int i2c_smbus_read_byte_data (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm2_touchkey_led_brightness_set (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static irqreturn_t tm2_touchkey_irq_handler(int irq, void *devid)
{
	struct tm2_touchkey_data *touchkey = devid;
	int data;
	int index;
	int i;

	if (touchkey->variant->no_reg)
		data = i2c_smbus_read_byte(touchkey->client);
	else
		data = i2c_smbus_read_byte_data(touchkey->client,
						touchkey->variant->keycode_reg);
	if (data < 0) {
		dev_err(&touchkey->client->dev,
			"failed to read i2c data: %d\n", data);
		goto out;
	}

	index = (data & TM2_TOUCHKEY_BIT_KEYCODE) - 1;
	if (index < 0 || index >= touchkey->num_keycodes) {
		dev_warn(&touchkey->client->dev,
			 "invalid keycode index %d\n", index);
		goto out;
	}

	if (data & TM2_TOUCHKEY_BIT_PRESS_EV) {
		for (i = 0; i < touchkey->num_keycodes; i++)
			input_report_key(touchkey->input_dev,
					 touchkey->keycodes[i], 0);
	} else {
		input_report_key(touchkey->input_dev,
				 touchkey->keycodes[index], 1);
	}

	input_sync(touchkey->input_dev);

out:
	if (touchkey->variant->fixed_regulator &&
				data & TM2_TOUCHKEY_BIT_PRESS_EV) {
		/* touch turns backlight on, so make sure we're in sync */
		if (touchkey->led_dev.brightness == LED_OFF)
			tm2_touchkey_led_brightness_set(&touchkey->led_dev,
							LED_OFF);
	}

	return IRQ_HANDLED;
}