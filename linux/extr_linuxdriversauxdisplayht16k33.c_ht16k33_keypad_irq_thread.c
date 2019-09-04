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
struct ht16k33_keypad {scalar_t__ stopped; int /*<<< orphan*/  debounce_ms; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ ht16k33_keypad_scan (struct ht16k33_keypad*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ht16k33_keypad_irq_thread(int irq, void *dev)
{
	struct ht16k33_keypad *keypad = dev;

	do {
		wait_event_timeout(keypad->wait, keypad->stopped,
				    msecs_to_jiffies(keypad->debounce_ms));
		if (keypad->stopped)
			break;
	} while (ht16k33_keypad_scan(keypad));

	return IRQ_HANDLED;
}