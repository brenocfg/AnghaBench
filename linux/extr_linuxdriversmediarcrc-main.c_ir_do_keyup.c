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
struct rc_dev {int keypressed; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  last_keycode; int /*<<< orphan*/  timer_repeat; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_feedback ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ir_do_keyup(struct rc_dev *dev, bool sync)
{
	if (!dev->keypressed)
		return;

	dev_dbg(&dev->dev, "keyup key 0x%04x\n", dev->last_keycode);
	del_timer(&dev->timer_repeat);
	input_report_key(dev->input_dev, dev->last_keycode, 0);
	led_trigger_event(led_feedback, LED_OFF);
	if (sync)
		input_sync(dev->input_dev);
	dev->keypressed = false;
}