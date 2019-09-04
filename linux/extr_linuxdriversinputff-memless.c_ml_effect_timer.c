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
struct ml_device {struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 struct ml_device* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ml_device* ml ; 
 int /*<<< orphan*/  ml_play_effects (struct ml_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ml_effect_timer(struct timer_list *t)
{
	struct ml_device *ml = from_timer(ml, t, timer);
	struct input_dev *dev = ml->dev;
	unsigned long flags;

	pr_debug("timer: updating effects\n");

	spin_lock_irqsave(&dev->event_lock, flags);
	ml_play_effects(ml);
	spin_unlock_irqrestore(&dev->event_lock, flags);
}