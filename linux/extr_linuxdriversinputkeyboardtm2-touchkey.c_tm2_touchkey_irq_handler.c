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
struct tm2_touchkey_data {int /*<<< orphan*/  input_dev; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int KEY_BACK ; 
 int KEY_PHONE ; 
 int TM2_TOUCHKEY_BIT_KEYCODE ; 
 int TM2_TOUCHKEY_BIT_PRESS_EV ; 
 int /*<<< orphan*/  TM2_TOUCHKEY_KEYCODE_REG ; 
#define  TM2_TOUCHKEY_KEY_BACK 129 
#define  TM2_TOUCHKEY_KEY_MENU 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tm2_touchkey_irq_handler(int irq, void *devid)
{
	struct tm2_touchkey_data *touchkey = devid;
	int data;
	int key;

	data = i2c_smbus_read_byte_data(touchkey->client,
					TM2_TOUCHKEY_KEYCODE_REG);
	if (data < 0) {
		dev_err(&touchkey->client->dev,
			"failed to read i2c data: %d\n", data);
		goto out;
	}

	switch (data & TM2_TOUCHKEY_BIT_KEYCODE) {
	case TM2_TOUCHKEY_KEY_MENU:
		key = KEY_PHONE;
		break;

	case TM2_TOUCHKEY_KEY_BACK:
		key = KEY_BACK;
		break;

	default:
		dev_warn(&touchkey->client->dev,
			 "unhandled keycode, data %#02x\n", data);
		goto out;
	}

	if (data & TM2_TOUCHKEY_BIT_PRESS_EV) {
		input_report_key(touchkey->input_dev, KEY_PHONE, 0);
		input_report_key(touchkey->input_dev, KEY_BACK, 0);
	} else {
		input_report_key(touchkey->input_dev, key, 1);
	}

	input_sync(touchkey->input_dev);

out:
	return IRQ_HANDLED;
}