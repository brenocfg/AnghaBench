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
struct tw {int touched; unsigned char* data; scalar_t__ idx; struct input_dev* dev; } ;
struct serio {int dummy; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TW_LENGTH ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 struct tw* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t tw_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct tw *tw = serio_get_drvdata(serio);
	struct input_dev *dev = tw->dev;

	if (data) {		/* touch */
		tw->touched = 1;
		tw->data[tw->idx++] = data;
		/* verify length and that the two Y's are the same */
		if (tw->idx == TW_LENGTH && tw->data[1] == tw->data[2]) {
			input_report_abs(dev, ABS_X, tw->data[0]);
			input_report_abs(dev, ABS_Y, tw->data[1]);
			input_report_key(dev, BTN_TOUCH, 1);
			input_sync(dev);
			tw->idx = 0;
		}
	} else if (tw->touched) {	/* untouch */
		input_report_key(dev, BTN_TOUCH, 0);
		input_sync(dev);
		tw->idx = 0;
		tw->touched = 0;
	}

	return IRQ_HANDLED;
}