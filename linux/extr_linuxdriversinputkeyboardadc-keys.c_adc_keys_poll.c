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
typedef  scalar_t__ u32 ;
struct input_polled_dev {int /*<<< orphan*/  input; struct adc_keys_state* private; } ;
struct adc_keys_state {int keyup_voltage; int num_keys; int last_key; TYPE_1__* map; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int voltage; int keycode; } ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void adc_keys_poll(struct input_polled_dev *dev)
{
	struct adc_keys_state *st = dev->private;
	int i, value, ret;
	u32 diff, closest = 0xffffffff;
	int keycode = 0;

	ret = iio_read_channel_processed(st->channel, &value);
	if (unlikely(ret < 0)) {
		/* Forcibly release key if any was pressed */
		value = st->keyup_voltage;
	} else {
		for (i = 0; i < st->num_keys; i++) {
			diff = abs(st->map[i].voltage - value);
			if (diff < closest) {
				closest = diff;
				keycode = st->map[i].keycode;
			}
		}
	}

	if (abs(st->keyup_voltage - value) < closest)
		keycode = 0;

	if (st->last_key && st->last_key != keycode)
		input_report_key(dev->input, st->last_key, 0);

	if (keycode)
		input_report_key(dev->input, keycode, 1);

	input_sync(dev->input);
	st->last_key = keycode;
}