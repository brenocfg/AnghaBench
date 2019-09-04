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
typedef  int /*<<< orphan*/  u8 ;
struct input_dev {int dummy; } ;
struct exc3000_data {int /*<<< orphan*/  prop; int /*<<< orphan*/  timer; int /*<<< orphan*/  client; int /*<<< orphan*/ * buf; struct input_dev* input; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXC3000_LEN_FRAME ; 
 int /*<<< orphan*/  EXC3000_SLOTS_PER_FRAME ; 
 int /*<<< orphan*/  EXC3000_TIMEOUT_MS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int exc3000_read_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  exc3000_report_slots (struct input_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t exc3000_interrupt(int irq, void *dev_id)
{
	struct exc3000_data *data = dev_id;
	struct input_dev *input = data->input;
	u8 *buf = data->buf;
	int slots, total_slots;
	int error;

	error = exc3000_read_data(data->client, buf, &total_slots);
	if (error) {
		/* Schedule a timer to release "stuck" contacts */
		mod_timer(&data->timer,
			  jiffies + msecs_to_jiffies(EXC3000_TIMEOUT_MS));
		goto out;
	}

	/*
	 * We read full state successfully, no contacts will be "stuck".
	 */
	del_timer_sync(&data->timer);

	while (total_slots > 0) {
		slots = min(total_slots, EXC3000_SLOTS_PER_FRAME);
		exc3000_report_slots(input, &data->prop, buf + 4, slots);
		total_slots -= slots;
		buf += EXC3000_LEN_FRAME;
	}

	input_mt_sync_frame(input);
	input_sync(input);

out:
	return IRQ_HANDLED;
}