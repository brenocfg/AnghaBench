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
struct rc_dev {int /*<<< orphan*/  dev; TYPE_1__* raw; } ;
struct ir_raw_event {scalar_t__ duration; int pulse; scalar_t__ reset; } ;
struct imon_dec {int state; int bits; int last_chk; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {struct imon_dec imon; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IMON_BITS ; 
 int IMON_CHKBITS ; 
 int IMON_UNIT ; 
 scalar_t__ MS_TO_NS (int) ; 
#define  STATE_BIT_CHK 131 
#define  STATE_BIT_START 130 
 int STATE_ERROR ; 
#define  STATE_FINISHED 129 
#define  STATE_INACTIVE 128 
 int /*<<< orphan*/  TO_STR (int) ; 
 int /*<<< orphan*/  TO_US (scalar_t__) ; 
 int /*<<< orphan*/  decrease_duration (struct ir_raw_event*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geq_margin (scalar_t__,int,int) ; 
 int /*<<< orphan*/  ir_imon_decode_scancode (struct rc_dev*) ; 
 int /*<<< orphan*/  is_timing_event (struct ir_raw_event) ; 

__attribute__((used)) static int ir_imon_decode(struct rc_dev *dev, struct ir_raw_event ev)
{
	struct imon_dec *data = &dev->raw->imon;

	if (!is_timing_event(ev)) {
		if (ev.reset)
			data->state = STATE_INACTIVE;
		return 0;
	}

	dev_dbg(&dev->dev,
		"iMON decode started at state %d bitno %d (%uus %s)\n",
		data->state, data->count, TO_US(ev.duration),
		TO_STR(ev.pulse));

	/*
	 * Since iMON protocol is a series of bits, if at any point
	 * we encounter an error, make sure that any remaining bits
	 * aren't parsed as a scancode made up of less bits.
	 *
	 * Note that if the stick is held, then the remote repeats
	 * the scancode with about 12ms between them. So, make sure
	 * we have at least 10ms of space after an error. That way,
	 * we're at a new scancode.
	 */
	if (data->state == STATE_ERROR) {
		if (!ev.pulse && ev.duration > MS_TO_NS(10))
			data->state = STATE_INACTIVE;
		return 0;
	}

	for (;;) {
		if (!geq_margin(ev.duration, IMON_UNIT, IMON_UNIT / 2))
			return 0;

		decrease_duration(&ev, IMON_UNIT);

		switch (data->state) {
		case STATE_INACTIVE:
			if (ev.pulse) {
				data->state = STATE_BIT_CHK;
				data->bits = 0;
				data->count = IMON_BITS;
			}
			break;
		case STATE_BIT_CHK:
			if (IMON_CHKBITS & BIT(data->count))
				data->last_chk = ev.pulse;
			else if (ev.pulse)
				goto err_out;
			data->state = STATE_BIT_START;
			break;
		case STATE_BIT_START:
			data->bits <<= 1;
			if (!ev.pulse)
				data->bits |= 1;

			if (IMON_CHKBITS & BIT(data->count)) {
				if (data->last_chk != !(data->bits & 3))
					goto err_out;
			}

			if (!data->count--)
				data->state = STATE_FINISHED;
			else
				data->state = STATE_BIT_CHK;
			break;
		case STATE_FINISHED:
			if (ev.pulse)
				goto err_out;
			ir_imon_decode_scancode(dev);
			data->state = STATE_INACTIVE;
			break;
		}
	}

err_out:
	dev_dbg(&dev->dev,
		"iMON decode failed at state %d bitno %d (%uus %s)\n",
		data->state, data->count, TO_US(ev.duration),
		TO_STR(ev.pulse));

	data->state = STATE_ERROR;

	return -EINVAL;
}