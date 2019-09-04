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
struct matrix_keypad {int stopped; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_row_irqs (struct matrix_keypad*) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 struct matrix_keypad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void matrix_keypad_stop(struct input_dev *dev)
{
	struct matrix_keypad *keypad = input_get_drvdata(dev);

	spin_lock_irq(&keypad->lock);
	keypad->stopped = true;
	spin_unlock_irq(&keypad->lock);

	flush_delayed_work(&keypad->work);
	/*
	 * matrix_keypad_scan() will leave IRQs enabled;
	 * we should disable them now.
	 */
	disable_row_irqs(keypad);
}