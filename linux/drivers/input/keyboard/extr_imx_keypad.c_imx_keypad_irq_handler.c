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
struct imx_keypad {int /*<<< orphan*/  check_matrix_timer; scalar_t__ stable_count; scalar_t__ enabled; scalar_t__ mmio_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned short KBD_STAT_KDIE ; 
 unsigned short KBD_STAT_KPKD ; 
 unsigned short KBD_STAT_KPKR ; 
 unsigned short KBD_STAT_KRIE ; 
 scalar_t__ KPSR ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 unsigned short readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static irqreturn_t imx_keypad_irq_handler(int irq, void *dev_id)
{
	struct imx_keypad *keypad = dev_id;
	unsigned short reg_val;

	reg_val = readw(keypad->mmio_base + KPSR);

	/* Disable both interrupt types */
	reg_val &= ~(KBD_STAT_KRIE | KBD_STAT_KDIE);
	/* Clear interrupts status bits */
	reg_val |= KBD_STAT_KPKR | KBD_STAT_KPKD;
	writew(reg_val, keypad->mmio_base + KPSR);

	if (keypad->enabled) {
		/* The matrix is supposed to be changed */
		keypad->stable_count = 0;

		/* Schedule the scanning procedure near in the future */
		mod_timer(&keypad->check_matrix_timer,
			  jiffies + msecs_to_jiffies(2));
	}

	return IRQ_HANDLED;
}