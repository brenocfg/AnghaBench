#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct rc_dev {int keypressed; int last_protocol; scalar_t__ last_scancode; scalar_t__ last_toggle; scalar_t__ allowed_protocols; TYPE_1__* input_dev; int /*<<< orphan*/  timer_repeat; int /*<<< orphan*/  device_name; int /*<<< orphan*/  dev; scalar_t__ last_keycode; } ;
struct lirc_scancode {scalar_t__ scancode; int rc_proto; scalar_t__ keycode; int /*<<< orphan*/  flags; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;
struct TYPE_4__ {scalar_t__* rep; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 scalar_t__ KEY_RESERVED ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LIRC_SCANCODE_FLAG_TOGGLE ; 
 scalar_t__ MSC_SCAN ; 
 scalar_t__ RC_PROTO_BIT_CEC ; 
 size_t REP_DELAY ; 
 size_t REP_PERIOD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  input_event (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  input_report_key (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  input_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_do_keyup (struct rc_dev*,int) ; 
 int /*<<< orphan*/  ir_lirc_scancode_event (struct rc_dev*,struct lirc_scancode*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_feedback ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ir_do_keydown(struct rc_dev *dev, enum rc_proto protocol,
			  u32 scancode, u32 keycode, u8 toggle)
{
	bool new_event = (!dev->keypressed		 ||
			  dev->last_protocol != protocol ||
			  dev->last_scancode != scancode ||
			  dev->last_toggle   != toggle);
	struct lirc_scancode sc = {
		.scancode = scancode, .rc_proto = protocol,
		.flags = toggle ? LIRC_SCANCODE_FLAG_TOGGLE : 0,
		.keycode = keycode
	};

	if (dev->allowed_protocols != RC_PROTO_BIT_CEC)
		ir_lirc_scancode_event(dev, &sc);

	if (new_event && dev->keypressed)
		ir_do_keyup(dev, false);

	input_event(dev->input_dev, EV_MSC, MSC_SCAN, scancode);

	dev->last_protocol = protocol;
	dev->last_scancode = scancode;
	dev->last_toggle = toggle;
	dev->last_keycode = keycode;

	if (new_event && keycode != KEY_RESERVED) {
		/* Register a keypress */
		dev->keypressed = true;

		dev_dbg(&dev->dev, "%s: key down event, key 0x%04x, protocol 0x%04x, scancode 0x%08x\n",
			dev->device_name, keycode, protocol, scancode);
		input_report_key(dev->input_dev, keycode, 1);

		led_trigger_event(led_feedback, LED_FULL);
	}

	/*
	 * For CEC, start sending repeat messages as soon as the first
	 * repeated message is sent, as long as REP_DELAY = 0 and REP_PERIOD
	 * is non-zero. Otherwise, the input layer will generate repeat
	 * messages.
	 */
	if (!new_event && keycode != KEY_RESERVED &&
	    dev->allowed_protocols == RC_PROTO_BIT_CEC &&
	    !timer_pending(&dev->timer_repeat) &&
	    dev->input_dev->rep[REP_PERIOD] &&
	    !dev->input_dev->rep[REP_DELAY]) {
		input_event(dev->input_dev, EV_KEY, keycode, 2);
		mod_timer(&dev->timer_repeat, jiffies +
			  msecs_to_jiffies(dev->input_dev->rep[REP_PERIOD]));
	}

	input_sync(dev->input_dev);
}