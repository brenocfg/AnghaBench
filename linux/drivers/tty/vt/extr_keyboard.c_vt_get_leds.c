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
struct kbd_struct {int dummy; } ;

/* Variables and functions */
 struct kbd_struct* kbd_table ; 
 int /*<<< orphan*/  led_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vc_kbd_led (struct kbd_struct*,int) ; 

int vt_get_leds(int console, int flag)
{
	struct kbd_struct *kb = kbd_table + console;
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&led_lock, flags);
	ret = vc_kbd_led(kb, flag);
	spin_unlock_irqrestore(&led_lock, flags);

	return ret;
}