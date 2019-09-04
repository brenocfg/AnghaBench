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
typedef  int u8 ;
struct qt1070_data {int last_keys; int /*<<< orphan*/ * keycodes; struct input_dev* input; struct i2c_client* client; } ;
struct input_dev {int dummy; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DET_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_STATUS ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  qt1070_key2code ; 
 int qt1070_read (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t qt1070_interrupt(int irq, void *dev_id)
{
	struct qt1070_data *data = dev_id;
	struct i2c_client *client = data->client;
	struct input_dev *input = data->input;
	int i;
	u8 new_keys, keyval, mask = 0x01;

	/* Read the detected status register, thus clearing interrupt */
	qt1070_read(client, DET_STATUS);

	/* Read which key changed */
	new_keys = qt1070_read(client, KEY_STATUS);

	for (i = 0; i < ARRAY_SIZE(qt1070_key2code); i++) {
		keyval = new_keys & mask;
		if ((data->last_keys & mask) != keyval)
			input_report_key(input, data->keycodes[i], keyval);
		mask <<= 1;
	}
	input_sync(input);

	data->last_keys = new_keys;
	return IRQ_HANDLED;
}