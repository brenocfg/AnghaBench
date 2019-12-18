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
struct timer_list {int dummy; } ;
struct input_value {int member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct input_dev {int /*<<< orphan*/  event_lock; scalar_t__* rep; int /*<<< orphan*/  timer; int /*<<< orphan*/  repeat_key; int /*<<< orphan*/  keybit; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct input_value*) ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  KEY_MAX ; 
 size_t REP_PERIOD ; 
 struct input_dev* dev ; 
 struct input_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_pass_values (struct input_dev*,struct input_value*,int /*<<< orphan*/ ) ; 
 struct input_value input_value_sync ; 
 scalar_t__ is_event_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void input_repeat_key(struct timer_list *t)
{
	struct input_dev *dev = from_timer(dev, t, timer);
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);

	if (test_bit(dev->repeat_key, dev->key) &&
	    is_event_supported(dev->repeat_key, dev->keybit, KEY_MAX)) {
		struct input_value vals[] =  {
			{ EV_KEY, dev->repeat_key, 2 },
			input_value_sync
		};

		input_pass_values(dev, vals, ARRAY_SIZE(vals));

		if (dev->rep[REP_PERIOD])
			mod_timer(&dev->timer, jiffies +
					msecs_to_jiffies(dev->rep[REP_PERIOD]));
	}

	spin_unlock_irqrestore(&dev->event_lock, flags);
}