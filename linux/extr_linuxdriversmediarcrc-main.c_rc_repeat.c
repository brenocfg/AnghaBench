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
struct rc_dev {scalar_t__ allowed_protocols; int /*<<< orphan*/  keylock; scalar_t__ keyup_jiffies; int /*<<< orphan*/  timer_keyup; scalar_t__ keypressed; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  last_scancode; int /*<<< orphan*/  last_toggle; int /*<<< orphan*/  last_keycode; int /*<<< orphan*/  last_protocol; int /*<<< orphan*/  timeout; } ;
struct lirc_scancode {int flags; int /*<<< orphan*/  keycode; int /*<<< orphan*/  rc_proto; int /*<<< orphan*/  scancode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int LIRC_SCANCODE_FLAG_REPEAT ; 
 int LIRC_SCANCODE_FLAG_TOGGLE ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 scalar_t__ RC_PROTO_BIT_CEC ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_lirc_scancode_event (struct rc_dev*,struct lirc_scancode*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned int nsecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repeat_period (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rc_repeat(struct rc_dev *dev)
{
	unsigned long flags;
	unsigned int timeout = nsecs_to_jiffies(dev->timeout) +
		msecs_to_jiffies(repeat_period(dev->last_protocol));
	struct lirc_scancode sc = {
		.scancode = dev->last_scancode, .rc_proto = dev->last_protocol,
		.keycode = dev->keypressed ? dev->last_keycode : KEY_RESERVED,
		.flags = LIRC_SCANCODE_FLAG_REPEAT |
			 (dev->last_toggle ? LIRC_SCANCODE_FLAG_TOGGLE : 0)
	};

	if (dev->allowed_protocols != RC_PROTO_BIT_CEC)
		ir_lirc_scancode_event(dev, &sc);

	spin_lock_irqsave(&dev->keylock, flags);

	input_event(dev->input_dev, EV_MSC, MSC_SCAN, dev->last_scancode);
	input_sync(dev->input_dev);

	if (dev->keypressed) {
		dev->keyup_jiffies = jiffies + timeout;
		mod_timer(&dev->timer_keyup, dev->keyup_jiffies);
	}

	spin_unlock_irqrestore(&dev->keylock, flags);
}