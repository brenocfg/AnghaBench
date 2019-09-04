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
struct tca6507_led {scalar_t__ offtime; scalar_t__ ontime; struct tca6507_chip* chip; } ;
struct tca6507_chip {int /*<<< orphan*/  work; scalar_t__ reg_set; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int led_prepare (struct tca6507_led*) ; 
 int /*<<< orphan*/  led_release (struct tca6507_led*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int led_assign(struct tca6507_led *led)
{
	struct tca6507_chip *tca = led->chip;
	int err;
	unsigned long flags;

	spin_lock_irqsave(&tca->lock, flags);
	led_release(led);
	err = led_prepare(led);
	if (err) {
		/*
		 * Can only fail on timer setup.  In that case we need
		 * to re-establish as steady level.
		 */
		led->ontime = 0;
		led->offtime = 0;
		led_prepare(led);
	}
	spin_unlock_irqrestore(&tca->lock, flags);

	if (tca->reg_set)
		schedule_work(&tca->work);
	return err;
}