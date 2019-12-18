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
typedef  int u8 ;
typedef  int u32 ;
struct rc_dev {int /*<<< orphan*/  dev; TYPE_1__* raw; } ;
struct rc6_dec {int state; int count; int header; int toggle; int body; int wanted_bits; } ;
struct ir_raw_event {int pulse; int /*<<< orphan*/  duration; scalar_t__ reset; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;
struct TYPE_2__ {struct rc6_dec rc6; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 int EINVAL ; 
 int RC6_0_NBITS ; 
#define  RC6_6A_KATHREIN_CC 141 
 int RC6_6A_LCC_MASK ; 
#define  RC6_6A_MCE_CC 140 
 int RC6_6A_MCE_TOGGLE_MASK ; 
 int RC6_6A_NBITS ; 
#define  RC6_6A_ZOTAC_CC 139 
 int /*<<< orphan*/  RC6_BIT_END ; 
 int /*<<< orphan*/  RC6_BIT_START ; 
 int RC6_HEADER_NBITS ; 
#define  RC6_MODE_0 138 
#define  RC6_MODE_6A 137 
 int /*<<< orphan*/  RC6_PREFIX_PULSE ; 
 int /*<<< orphan*/  RC6_PREFIX_SPACE ; 
 int RC6_STARTBIT_MASK ; 
 int RC6_SUFFIX_SPACE ; 
 int /*<<< orphan*/  RC6_TOGGLE_END ; 
 int /*<<< orphan*/  RC6_TOGGLE_START ; 
 int RC6_UNIT ; 
 int RC_PROTO_RC6_0 ; 
 int RC_PROTO_RC6_6A_20 ; 
 int RC_PROTO_RC6_6A_24 ; 
 int RC_PROTO_RC6_6A_32 ; 
 int RC_PROTO_RC6_MCE ; 
#define  STATE_BODY_BIT_END 136 
#define  STATE_BODY_BIT_START 135 
#define  STATE_FINISHED 134 
#define  STATE_HEADER_BIT_END 133 
#define  STATE_HEADER_BIT_START 132 
#define  STATE_INACTIVE 131 
#define  STATE_PREFIX_SPACE 130 
#define  STATE_TOGGLE_END 129 
#define  STATE_TOGGLE_START 128 
 int TO_STR (int) ; 
 int TO_US (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrease_duration (struct ir_raw_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  eq_margin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ geq_margin (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  is_timing_event (struct ir_raw_event) ; 
 int const rc6_mode (struct rc6_dec*) ; 
 int /*<<< orphan*/  rc_keydown (struct rc_dev*,int,int,int) ; 

__attribute__((used)) static int ir_rc6_decode(struct rc_dev *dev, struct ir_raw_event ev)
{
	struct rc6_dec *data = &dev->raw->rc6;
	u32 scancode;
	u8 toggle;
	enum rc_proto protocol;

	if (!is_timing_event(ev)) {
		if (ev.reset)
			data->state = STATE_INACTIVE;
		return 0;
	}

	if (!geq_margin(ev.duration, RC6_UNIT, RC6_UNIT / 2))
		goto out;

again:
	dev_dbg(&dev->dev, "RC6 decode started at state %i (%uus %s)\n",
		data->state, TO_US(ev.duration), TO_STR(ev.pulse));

	if (!geq_margin(ev.duration, RC6_UNIT, RC6_UNIT / 2))
		return 0;

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.pulse)
			break;

		/* Note: larger margin on first pulse since each RC6_UNIT
		   is quite short and some hardware takes some time to
		   adjust to the signal */
		if (!eq_margin(ev.duration, RC6_PREFIX_PULSE, RC6_UNIT))
			break;

		data->state = STATE_PREFIX_SPACE;
		data->count = 0;
		return 0;

	case STATE_PREFIX_SPACE:
		if (ev.pulse)
			break;

		if (!eq_margin(ev.duration, RC6_PREFIX_SPACE, RC6_UNIT / 2))
			break;

		data->state = STATE_HEADER_BIT_START;
		data->header = 0;
		return 0;

	case STATE_HEADER_BIT_START:
		if (!eq_margin(ev.duration, RC6_BIT_START, RC6_UNIT / 2))
			break;

		data->header <<= 1;
		if (ev.pulse)
			data->header |= 1;
		data->count++;
		data->state = STATE_HEADER_BIT_END;
		return 0;

	case STATE_HEADER_BIT_END:
		if (data->count == RC6_HEADER_NBITS)
			data->state = STATE_TOGGLE_START;
		else
			data->state = STATE_HEADER_BIT_START;

		decrease_duration(&ev, RC6_BIT_END);
		goto again;

	case STATE_TOGGLE_START:
		if (!eq_margin(ev.duration, RC6_TOGGLE_START, RC6_UNIT / 2))
			break;

		data->toggle = ev.pulse;
		data->state = STATE_TOGGLE_END;
		return 0;

	case STATE_TOGGLE_END:
		if (!(data->header & RC6_STARTBIT_MASK)) {
			dev_dbg(&dev->dev, "RC6 invalid start bit\n");
			break;
		}

		data->state = STATE_BODY_BIT_START;
		decrease_duration(&ev, RC6_TOGGLE_END);
		data->count = 0;
		data->body = 0;

		switch (rc6_mode(data)) {
		case RC6_MODE_0:
			data->wanted_bits = RC6_0_NBITS;
			break;
		case RC6_MODE_6A:
			data->wanted_bits = RC6_6A_NBITS;
			break;
		default:
			dev_dbg(&dev->dev, "RC6 unknown mode\n");
			goto out;
		}
		goto again;

	case STATE_BODY_BIT_START:
		if (eq_margin(ev.duration, RC6_BIT_START, RC6_UNIT / 2)) {
			/* Discard LSB's that won't fit in data->body */
			if (data->count++ < CHAR_BIT * sizeof data->body) {
				data->body <<= 1;
				if (ev.pulse)
					data->body |= 1;
			}
			data->state = STATE_BODY_BIT_END;
			return 0;
		} else if (RC6_MODE_6A == rc6_mode(data) && !ev.pulse &&
				geq_margin(ev.duration, RC6_SUFFIX_SPACE, RC6_UNIT / 2)) {
			data->state = STATE_FINISHED;
			goto again;
		}
		break;

	case STATE_BODY_BIT_END:
		if (data->count == data->wanted_bits)
			data->state = STATE_FINISHED;
		else
			data->state = STATE_BODY_BIT_START;

		decrease_duration(&ev, RC6_BIT_END);
		goto again;

	case STATE_FINISHED:
		if (ev.pulse)
			break;

		switch (rc6_mode(data)) {
		case RC6_MODE_0:
			scancode = data->body;
			toggle = data->toggle;
			protocol = RC_PROTO_RC6_0;
			dev_dbg(&dev->dev, "RC6(0) scancode 0x%04x (toggle: %u)\n",
				scancode, toggle);
			break;

		case RC6_MODE_6A:
			if (data->count > CHAR_BIT * sizeof data->body) {
				dev_dbg(&dev->dev, "RC6 too many (%u) data bits\n",
					data->count);
				goto out;
			}

			scancode = data->body;
			switch (data->count) {
			case 20:
				protocol = RC_PROTO_RC6_6A_20;
				toggle = 0;
				break;
			case 24:
				protocol = RC_PROTO_RC6_6A_24;
				toggle = 0;
				break;
			case 32:
				switch (scancode & RC6_6A_LCC_MASK) {
				case RC6_6A_MCE_CC:
				case RC6_6A_KATHREIN_CC:
				case RC6_6A_ZOTAC_CC:
					protocol = RC_PROTO_RC6_MCE;
					toggle = !!(scancode & RC6_6A_MCE_TOGGLE_MASK);
					scancode &= ~RC6_6A_MCE_TOGGLE_MASK;
					break;
				default:
					protocol = RC_PROTO_RC6_6A_32;
					toggle = 0;
					break;
				}
				break;
			default:
				dev_dbg(&dev->dev, "RC6(6A) unsupported length\n");
				goto out;
			}

			dev_dbg(&dev->dev, "RC6(6A) proto 0x%04x, scancode 0x%08x (toggle: %u)\n",
				protocol, scancode, toggle);
			break;
		default:
			dev_dbg(&dev->dev, "RC6 unknown mode\n");
			goto out;
		}

		rc_keydown(dev, protocol, scancode, toggle);
		data->state = STATE_INACTIVE;
		return 0;
	}

out:
	dev_dbg(&dev->dev, "RC6 decode failed at state %i (%uus %s)\n",
		data->state, TO_US(ev.duration), TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	return -EINVAL;
}