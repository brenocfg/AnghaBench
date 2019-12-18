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

/* Variables and functions */
 int /*<<< orphan*/  KEY_DOWN ; 
 int /*<<< orphan*/  PRESSED ; 
 int /*<<< orphan*/  RELEASED ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  reporting_keystroke ; 
 int /*<<< orphan*/  virt_keyboard ; 

void speakup_fake_down_arrow(void)
{
	unsigned long flags;

	/* disable keyboard interrupts */
	local_irq_save(flags);
	/* don't change CPU */
	preempt_disable();

	__this_cpu_write(reporting_keystroke, true);
	input_report_key(virt_keyboard, KEY_DOWN, PRESSED);
	input_report_key(virt_keyboard, KEY_DOWN, RELEASED);
	input_sync(virt_keyboard);
	__this_cpu_write(reporting_keystroke, false);

	/* reenable preemption */
	preempt_enable();
	/* reenable keyboard interrupts */
	local_irq_restore(flags);
}