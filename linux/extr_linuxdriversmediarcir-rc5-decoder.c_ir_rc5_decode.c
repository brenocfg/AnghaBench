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
struct rc_dev {int enabled_protocols; int /*<<< orphan*/  dev; TYPE_1__* raw; } ;
struct rc5_dec {int state; int count; int bits; int is_rc5x; } ;
struct ir_raw_event {int /*<<< orphan*/  pulse; int /*<<< orphan*/  duration; scalar_t__ reset; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;
struct TYPE_2__ {struct rc5_dec rc5; } ;

/* Variables and functions */
 int CHECK_RC5X_NBITS ; 
 int EINVAL ; 
 int RC5X_NBITS ; 
 int RC5X_SPACE ; 
 int RC5_BIT_END ; 
 int RC5_BIT_START ; 
 int RC5_NBITS ; 
 int RC5_SZ_NBITS ; 
 int RC5_TRAILER ; 
 int RC5_UNIT ; 
 int RC_PROTO_BIT_RC5 ; 
 int RC_PROTO_BIT_RC5X_20 ; 
 int RC_PROTO_BIT_RC5_SZ ; 
 int RC_PROTO_RC5 ; 
 int RC_PROTO_RC5X_20 ; 
 int RC_PROTO_RC5_SZ ; 
#define  STATE_BIT_END 132 
#define  STATE_BIT_START 131 
#define  STATE_CHECK_RC5X 130 
#define  STATE_FINISHED 129 
#define  STATE_INACTIVE 128 
 int /*<<< orphan*/  TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_US (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrease_duration (struct ir_raw_event*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int,...) ; 
 int /*<<< orphan*/  eq_margin (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ geq_margin (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  is_timing_event (struct ir_raw_event) ; 
 int /*<<< orphan*/  rc_keydown (struct rc_dev*,int,int,int) ; 

__attribute__((used)) static int ir_rc5_decode(struct rc_dev *dev, struct ir_raw_event ev)
{
	struct rc5_dec *data = &dev->raw->rc5;
	u8 toggle;
	u32 scancode;
	enum rc_proto protocol;

	if (!is_timing_event(ev)) {
		if (ev.reset)
			data->state = STATE_INACTIVE;
		return 0;
	}

	if (!geq_margin(ev.duration, RC5_UNIT, RC5_UNIT / 2))
		goto out;

again:
	dev_dbg(&dev->dev, "RC5(x/sz) decode started at state %i (%uus %s)\n",
		data->state, TO_US(ev.duration), TO_STR(ev.pulse));

	if (!geq_margin(ev.duration, RC5_UNIT, RC5_UNIT / 2))
		return 0;

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.pulse)
			break;

		data->state = STATE_BIT_START;
		data->count = 1;
		decrease_duration(&ev, RC5_BIT_START);
		goto again;

	case STATE_BIT_START:
		if (!ev.pulse && geq_margin(ev.duration, RC5_TRAILER, RC5_UNIT / 2)) {
			data->state = STATE_FINISHED;
			goto again;
		}

		if (!eq_margin(ev.duration, RC5_BIT_START, RC5_UNIT / 2))
			break;

		data->bits <<= 1;
		if (!ev.pulse)
			data->bits |= 1;
		data->count++;
		data->state = STATE_BIT_END;
		return 0;

	case STATE_BIT_END:
		if (data->count == CHECK_RC5X_NBITS)
			data->state = STATE_CHECK_RC5X;
		else
			data->state = STATE_BIT_START;

		decrease_duration(&ev, RC5_BIT_END);
		goto again;

	case STATE_CHECK_RC5X:
		if (!ev.pulse && geq_margin(ev.duration, RC5X_SPACE, RC5_UNIT / 2)) {
			data->is_rc5x = true;
			decrease_duration(&ev, RC5X_SPACE);
		} else
			data->is_rc5x = false;
		data->state = STATE_BIT_START;
		goto again;

	case STATE_FINISHED:
		if (ev.pulse)
			break;

		if (data->is_rc5x && data->count == RC5X_NBITS) {
			/* RC5X */
			u8 xdata, command, system;
			if (!(dev->enabled_protocols & RC_PROTO_BIT_RC5X_20)) {
				data->state = STATE_INACTIVE;
				return 0;
			}
			xdata    = (data->bits & 0x0003F) >> 0;
			command  = (data->bits & 0x00FC0) >> 6;
			system   = (data->bits & 0x1F000) >> 12;
			toggle   = (data->bits & 0x20000) ? 1 : 0;
			command += (data->bits & 0x40000) ? 0 : 0x40;
			scancode = system << 16 | command << 8 | xdata;
			protocol = RC_PROTO_RC5X_20;

		} else if (!data->is_rc5x && data->count == RC5_NBITS) {
			/* RC5 */
			u8 command, system;
			if (!(dev->enabled_protocols & RC_PROTO_BIT_RC5)) {
				data->state = STATE_INACTIVE;
				return 0;
			}
			command  = (data->bits & 0x0003F) >> 0;
			system   = (data->bits & 0x007C0) >> 6;
			toggle   = (data->bits & 0x00800) ? 1 : 0;
			command += (data->bits & 0x01000) ? 0 : 0x40;
			scancode = system << 8 | command;
			protocol = RC_PROTO_RC5;

		} else if (!data->is_rc5x && data->count == RC5_SZ_NBITS) {
			/* RC5 StreamZap */
			u8 command, system;
			if (!(dev->enabled_protocols & RC_PROTO_BIT_RC5_SZ)) {
				data->state = STATE_INACTIVE;
				return 0;
			}
			command  = (data->bits & 0x0003F) >> 0;
			system   = (data->bits & 0x02FC0) >> 6;
			toggle   = (data->bits & 0x01000) ? 1 : 0;
			scancode = system << 6 | command;
			protocol = RC_PROTO_RC5_SZ;

		} else
			break;

		dev_dbg(&dev->dev, "RC5(x/sz) scancode 0x%06x (p: %u, t: %u)\n",
			scancode, protocol, toggle);

		rc_keydown(dev, protocol, scancode, toggle);
		data->state = STATE_INACTIVE;
		return 0;
	}

out:
	dev_dbg(&dev->dev, "RC5(x/sz) decode failed at state %i count %d (%uus %s)\n",
		data->state, data->count, TO_US(ev.duration), TO_STR(ev.pulse));
	data->state = STATE_INACTIVE;
	return -EINVAL;
}