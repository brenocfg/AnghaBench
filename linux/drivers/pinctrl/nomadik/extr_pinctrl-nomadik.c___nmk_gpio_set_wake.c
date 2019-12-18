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
struct nmk_gpio_chip {scalar_t__ sleepmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NMK_GPIO_SLPM_WAKEUP_ENABLE ; 
 int /*<<< orphan*/  WAKE ; 
 int /*<<< orphan*/  __nmk_gpio_irq_modify (struct nmk_gpio_chip*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __nmk_gpio_set_slpm (struct nmk_gpio_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __nmk_gpio_set_wake(struct nmk_gpio_chip *nmk_chip,
				int offset, bool on)
{
	/*
	 * Ensure WAKEUP_ENABLE is on.  No need to disable it if wakeup is
	 * disabled, since setting SLPM to 1 increases power consumption, and
	 * wakeup is anyhow controlled by the RIMSC and FIMSC registers.
	 */
	if (nmk_chip->sleepmode && on) {
		__nmk_gpio_set_slpm(nmk_chip, offset,
				    NMK_GPIO_SLPM_WAKEUP_ENABLE);
	}

	__nmk_gpio_irq_modify(nmk_chip, offset, WAKE, on);
}