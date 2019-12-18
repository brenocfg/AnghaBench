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
struct input_dev {int dummy; } ;
struct ep93xx_keypad {int* keycodes; int key1; int key2; scalar_t__ mmio_base; struct input_dev* input_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ KEY_REG ; 
 unsigned int KEY_REG_1KEY ; 
 unsigned int KEY_REG_2KEYS ; 
 unsigned int KEY_REG_KEY1_MASK ; 
 unsigned int KEY_REG_KEY1_SHIFT ; 
 unsigned int KEY_REG_KEY2_MASK ; 
 unsigned int KEY_REG_KEY2_SHIFT ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static irqreturn_t ep93xx_keypad_irq_handler(int irq, void *dev_id)
{
	struct ep93xx_keypad *keypad = dev_id;
	struct input_dev *input_dev = keypad->input_dev;
	unsigned int status;
	int keycode, key1, key2;

	status = __raw_readl(keypad->mmio_base + KEY_REG);

	keycode = (status & KEY_REG_KEY1_MASK) >> KEY_REG_KEY1_SHIFT;
	key1 = keypad->keycodes[keycode];

	keycode = (status & KEY_REG_KEY2_MASK) >> KEY_REG_KEY2_SHIFT;
	key2 = keypad->keycodes[keycode];

	if (status & KEY_REG_2KEYS) {
		if (keypad->key1 && key1 != keypad->key1 && key2 != keypad->key1)
			input_report_key(input_dev, keypad->key1, 0);

		if (keypad->key2 && key1 != keypad->key2 && key2 != keypad->key2)
			input_report_key(input_dev, keypad->key2, 0);

		input_report_key(input_dev, key1, 1);
		input_report_key(input_dev, key2, 1);

		keypad->key1 = key1;
		keypad->key2 = key2;

	} else if (status & KEY_REG_1KEY) {
		if (keypad->key1 && key1 != keypad->key1)
			input_report_key(input_dev, keypad->key1, 0);

		if (keypad->key2 && key1 != keypad->key2)
			input_report_key(input_dev, keypad->key2, 0);

		input_report_key(input_dev, key1, 1);

		keypad->key1 = key1;
		keypad->key2 = 0;

	} else {
		input_report_key(input_dev, keypad->key1, 0);
		input_report_key(input_dev, keypad->key2, 0);

		keypad->key1 = keypad->key2 = 0;
	}
	input_sync(input_dev);

	return IRQ_HANDLED;
}