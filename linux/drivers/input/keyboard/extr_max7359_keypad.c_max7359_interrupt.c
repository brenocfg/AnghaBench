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
struct max7359_keypad {int /*<<< orphan*/ * keycodes; TYPE_1__* client; struct input_dev* input_dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX7359_REG_KEYFIFO ; 
 int /*<<< orphan*/  MAX7359_ROW_SHIFT ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,char*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int max7359_read_reg (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t max7359_interrupt(int irq, void *dev_id)
{
	struct max7359_keypad *keypad = dev_id;
	struct input_dev *input_dev = keypad->input_dev;
	int val, row, col, release, code;

	val = max7359_read_reg(keypad->client, MAX7359_REG_KEYFIFO);
	row = val & 0x7;
	col = (val >> 3) & 0x7;
	release = val & 0x40;

	code = MATRIX_SCAN_CODE(row, col, MAX7359_ROW_SHIFT);

	dev_dbg(&keypad->client->dev,
		"key[%d:%d] %s\n", row, col, release ? "release" : "press");

	input_event(input_dev, EV_MSC, MSC_SCAN, code);
	input_report_key(input_dev, keypad->keycodes[code], !release);
	input_sync(input_dev);

	return IRQ_HANDLED;
}