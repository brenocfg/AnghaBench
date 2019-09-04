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
struct rc_dev {int /*<<< orphan*/  keylock; int /*<<< orphan*/  timer_repeat; int /*<<< orphan*/  last_keycode; scalar_t__ keypressed; struct input_dev* input_dev; } ;
struct input_dev {scalar_t__* rep; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 size_t REP_PERIOD ; 
 struct rc_dev* dev ; 
 struct rc_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_repeat ; 

__attribute__((used)) static void ir_timer_repeat(struct timer_list *t)
{
	struct rc_dev *dev = from_timer(dev, t, timer_repeat);
	struct input_dev *input = dev->input_dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->keylock, flags);
	if (dev->keypressed) {
		input_event(input, EV_KEY, dev->last_keycode, 2);
		input_sync(input);
		if (input->rep[REP_PERIOD])
			mod_timer(&dev->timer_repeat, jiffies +
				  msecs_to_jiffies(input->rep[REP_PERIOD]));
	}
	spin_unlock_irqrestore(&dev->keylock, flags);
}