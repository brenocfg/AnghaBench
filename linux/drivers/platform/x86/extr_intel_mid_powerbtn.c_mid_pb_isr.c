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
struct mid_pb_ddata {struct input_dev* input; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  mid_irq_ack (struct mid_pb_ddata*) ; 
 int mid_pbstat (struct mid_pb_ddata*,int*) ; 

__attribute__((used)) static irqreturn_t mid_pb_isr(int irq, void *dev_id)
{
	struct mid_pb_ddata *ddata = dev_id;
	struct input_dev *input = ddata->input;
	int value = 0;
	int ret;

	ret = mid_pbstat(ddata, &value);
	if (ret < 0) {
		dev_err(input->dev.parent,
			"Read error %d while reading MSIC_PB_STATUS\n", ret);
	} else {
		input_event(input, EV_KEY, KEY_POWER, value);
		input_sync(input);
	}

	mid_irq_ack(ddata);
	return IRQ_HANDLED;
}