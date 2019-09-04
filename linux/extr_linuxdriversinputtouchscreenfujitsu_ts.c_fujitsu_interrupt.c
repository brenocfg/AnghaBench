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
struct serio {int dummy; } ;
struct input_dev {int dummy; } ;
struct fujitsu {scalar_t__ idx; unsigned char* data; struct input_dev* dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ FUJITSU_LENGTH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 struct fujitsu* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t fujitsu_interrupt(struct serio *serio,
				     unsigned char data, unsigned int flags)
{
	struct fujitsu *fujitsu = serio_get_drvdata(serio);
	struct input_dev *dev = fujitsu->dev;

	if (fujitsu->idx == 0) {
		/* resync skip until start of frame */
		if ((data & 0xf0) != 0x80)
			return IRQ_HANDLED;
	} else {
		/* resync skip garbage */
		if (data & 0x80) {
			fujitsu->idx = 0;
			return IRQ_HANDLED;
		}
	}

	fujitsu->data[fujitsu->idx++] = data;
	if (fujitsu->idx == FUJITSU_LENGTH) {
		input_report_abs(dev, ABS_X,
				 (fujitsu->data[2] << 7) | fujitsu->data[1]);
		input_report_abs(dev, ABS_Y,
				 (fujitsu->data[4] << 7) | fujitsu->data[3]);
		input_report_key(dev, BTN_TOUCH,
				 (fujitsu->data[0] & 0x03) != 2);
		input_sync(dev);
		fujitsu->idx = 0;
	}

	return IRQ_HANDLED;
}