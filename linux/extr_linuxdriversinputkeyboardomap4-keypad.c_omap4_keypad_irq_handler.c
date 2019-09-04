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
struct omap4_keypad {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  OMAP4_KBD_IRQSTATUS ; 
 scalar_t__ kbd_read_irqreg (struct omap4_keypad*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t omap4_keypad_irq_handler(int irq, void *dev_id)
{
	struct omap4_keypad *keypad_data = dev_id;

	if (kbd_read_irqreg(keypad_data, OMAP4_KBD_IRQSTATUS))
		return IRQ_WAKE_THREAD;

	return IRQ_NONE;
}