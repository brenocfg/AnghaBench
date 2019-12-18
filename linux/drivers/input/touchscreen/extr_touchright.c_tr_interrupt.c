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
struct tr {unsigned char* data; size_t idx; struct input_dev* dev; } ;
struct serio {int dummy; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int TR_FORMAT_STATUS_BYTE ; 
 int TR_FORMAT_STATUS_MASK ; 
 int TR_FORMAT_TOUCH_BIT ; 
 size_t TR_LENGTH ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 struct tr* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t tr_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct tr *tr = serio_get_drvdata(serio);
	struct input_dev *dev = tr->dev;

	tr->data[tr->idx] = data;

	if ((tr->data[0] & TR_FORMAT_STATUS_MASK) == TR_FORMAT_STATUS_BYTE) {
		if (++tr->idx == TR_LENGTH) {
			input_report_abs(dev, ABS_X,
				(tr->data[1] << 5) | (tr->data[2] >> 1));
			input_report_abs(dev, ABS_Y,
				(tr->data[3] << 5) | (tr->data[4] >> 1));
			input_report_key(dev, BTN_TOUCH,
				tr->data[0] & TR_FORMAT_TOUCH_BIT);
			input_sync(dev);
			tr->idx = 0;
		}
	}

	return IRQ_HANDLED;
}