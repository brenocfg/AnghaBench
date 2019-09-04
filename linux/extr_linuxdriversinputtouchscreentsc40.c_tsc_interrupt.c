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
struct tsc_ser {unsigned char* data; size_t idx; struct input_dev* dev; } ;
struct serio {int /*<<< orphan*/  dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char,...) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 struct tsc_ser* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  tsc_process_data (struct tsc_ser*) ; 
 int /*<<< orphan*/  unlikely (unsigned char) ; 

__attribute__((used)) static irqreturn_t tsc_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct tsc_ser *ptsc = serio_get_drvdata(serio);
	struct input_dev *dev = ptsc->dev;

	ptsc->data[ptsc->idx] = data;
	switch (ptsc->idx++) {
	case 0:
		if (unlikely((data & 0x3e) != 0x10)) {
			dev_dbg(&serio->dev,
				"unsynchronized packet start (0x%02x)\n", data);
			ptsc->idx = 0;
		} else if (!(data & 0x01)) {
			input_report_key(dev, BTN_TOUCH, 0);
			input_sync(dev);
			ptsc->idx = 0;
		}
		break;

	case 1:
	case 3:
		if (unlikely(data & 0xfc)) {
			dev_dbg(&serio->dev,
				"unsynchronized data 0x%02x at offset %d\n",
				data, ptsc->idx - 1);
			ptsc->idx = 0;
		}
		break;

	case 4:
		tsc_process_data(ptsc);
		ptsc->idx = 0;
		break;
	}

	return IRQ_HANDLED;
}