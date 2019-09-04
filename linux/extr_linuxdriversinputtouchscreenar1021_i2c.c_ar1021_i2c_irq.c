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
struct input_dev {int dummy; } ;
struct ar1021_i2c {int* data; int /*<<< orphan*/  client; struct input_dev* input; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int BIT (int) ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static irqreturn_t ar1021_i2c_irq(int irq, void *dev_id)
{
	struct ar1021_i2c *ar1021 = dev_id;
	struct input_dev *input = ar1021->input;
	u8 *data = ar1021->data;
	unsigned int x, y, button;
	int retval;

	retval = i2c_master_recv(ar1021->client,
				 ar1021->data, sizeof(ar1021->data));
	if (retval != sizeof(ar1021->data))
		goto out;

	/* sync bit set ? */
	if (!(data[0] & BIT(7)))
		goto out;

	button = data[0] & BIT(0);
	x = ((data[2] & 0x1f) << 7) | (data[1] & 0x7f);
	y = ((data[4] & 0x1f) << 7) | (data[3] & 0x7f);

	input_report_abs(input, ABS_X, x);
	input_report_abs(input, ABS_Y, y);
	input_report_key(input, BTN_TOUCH, button);
	input_sync(input);

out:
	return IRQ_HANDLED;
}