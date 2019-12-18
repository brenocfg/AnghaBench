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
typedef  int u32 ;
struct sharp_dec {int state; int count; int bits; scalar_t__ pulse_len; } ;
struct rc_dev {int /*<<< orphan*/  dev; TYPE_1__* raw; } ;
struct ir_raw_event {int /*<<< orphan*/  pulse; scalar_t__ duration; scalar_t__ reset; } ;
struct TYPE_2__ {struct sharp_dec sharp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RC_PROTO_SHARP ; 
 int SHARP_BIT_0_PERIOD ; 
 int SHARP_BIT_1_PERIOD ; 
 int SHARP_BIT_PULSE ; 
 int SHARP_ECHO_SPACE ; 
 int SHARP_NBITS ; 
 int /*<<< orphan*/  SHARP_TRAILER_SPACE ; 
#define  STATE_BIT_PULSE 133 
#define  STATE_BIT_SPACE 132 
#define  STATE_ECHO_SPACE 131 
#define  STATE_INACTIVE 130 
#define  STATE_TRAILER_PULSE 129 
#define  STATE_TRAILER_SPACE 128 
 int /*<<< orphan*/  TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_US (scalar_t__) ; 
 int bitrev8 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  eq_margin (scalar_t__,int,int) ; 
 int /*<<< orphan*/  geq_margin (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_timing_event (struct ir_raw_event) ; 
 int /*<<< orphan*/  rc_keydown (struct rc_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ir_sharp_decode(struct rc_dev *dev, struct ir_raw_event ev)
{
	struct sharp_dec *data = &dev->raw->sharp;
	u32 msg, echo, address, command, scancode;

	if (!is_timing_event(ev)) {
		if (ev.reset)
			data->state = STATE_INACTIVE;
		return 0;
	}

	dev_dbg(&dev->dev, "Sharp decode started at state %d (%uus %s)\n",
		data->state, TO_US(ev.duration), TO_STR(ev.pulse));

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.pulse)
			break;

		if (!eq_margin(ev.duration, SHARP_BIT_PULSE,
			       SHARP_BIT_PULSE / 2))
			break;

		data->count = 0;
		data->pulse_len = ev.duration;
		data->state = STATE_BIT_SPACE;
		return 0;

	case STATE_BIT_PULSE:
		if (!ev.pulse)
			break;

		if (!eq_margin(ev.duration, SHARP_BIT_PULSE,
			       SHARP_BIT_PULSE / 2))
			break;

		data->pulse_len = ev.duration;
		data->state = STATE_BIT_SPACE;
		return 0;

	case STATE_BIT_SPACE:
		if (ev.pulse)
			break;

		data->bits <<= 1;
		if (eq_margin(data->pulse_len + ev.duration, SHARP_BIT_1_PERIOD,
			      SHARP_BIT_PULSE * 2))
			data->bits |= 1;
		else if (!eq_margin(data->pulse_len + ev.duration,
				    SHARP_BIT_0_PERIOD, SHARP_BIT_PULSE * 2))
			break;
		data->count++;

		if (data->count == SHARP_NBITS ||
		    data->count == SHARP_NBITS * 2)
			data->state = STATE_TRAILER_PULSE;
		else
			data->state = STATE_BIT_PULSE;

		return 0;

	case STATE_TRAILER_PULSE:
		if (!ev.pulse)
			break;

		if (!eq_margin(ev.duration, SHARP_BIT_PULSE,
			       SHARP_BIT_PULSE / 2))
			break;

		if (data->count == SHARP_NBITS) {
			/* exp,chk bits should be 1,0 */
			if ((data->bits & 0x3) != 0x2 &&
			/* DENON variant, both chk bits 0 */
			    (data->bits & 0x3) != 0x0)
				break;
			data->state = STATE_ECHO_SPACE;
		} else {
			data->state = STATE_TRAILER_SPACE;
		}
		return 0;

	case STATE_ECHO_SPACE:
		if (ev.pulse)
			break;

		if (!eq_margin(ev.duration, SHARP_ECHO_SPACE,
			       SHARP_ECHO_SPACE / 4))
			break;

		data->state = STATE_BIT_PULSE;

		return 0;

	case STATE_TRAILER_SPACE:
		if (ev.pulse)
			break;

		if (!geq_margin(ev.duration, SHARP_TRAILER_SPACE,
				SHARP_BIT_PULSE / 2))
			break;

		/* Validate - command, ext, chk should be inverted in 2nd */
		msg = (data->bits >> 15) & 0x7fff;
		echo = data->bits & 0x7fff;
		if ((msg ^ echo) != 0x3ff) {
			dev_dbg(&dev->dev,
				"Sharp checksum error: received 0x%04x, 0x%04x\n",
				msg, echo);
			break;
		}

		address = bitrev8((msg >> 7) & 0xf8);
		command = bitrev8((msg >> 2) & 0xff);

		scancode = address << 8 | command;
		dev_dbg(&dev->dev, "Sharp scancode 0x%04x\n", scancode);

		rc_keydown(dev, RC_PROTO_SHARP, scancode, 0);
		data->state = STATE_INACTIVE;
		return 0;
	}

	dev_dbg(&dev->dev, "Sharp decode failed at count %d state %d (%uus %s)\n",
		data->count, data->state, TO_US(ev.duration), TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	return -EINVAL;
}