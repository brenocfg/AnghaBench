#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int suspend_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PM_ULP0 ; 
#define  PM_SUSPEND_MEM 130 
#define  PM_SUSPEND_ON 129 
#define  PM_SUSPEND_STANDBY 128 
 int /*<<< orphan*/  at91_pm_suspend (int) ; 
 int /*<<< orphan*/  at91_pm_verify_clocks () ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 TYPE_1__ pm_data ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int at91_pm_enter(suspend_state_t state)
{
#ifdef CONFIG_PINCTRL_AT91
	at91_pinctrl_gpio_suspend();
#endif

	switch (state) {
	case PM_SUSPEND_MEM:
	case PM_SUSPEND_STANDBY:
		/*
		 * Ensure that clocks are in a valid state.
		 */
		if (pm_data.mode >= AT91_PM_ULP0 &&
		    !at91_pm_verify_clocks())
			goto error;

		at91_pm_suspend(state);

		break;

	case PM_SUSPEND_ON:
		cpu_do_idle();
		break;

	default:
		pr_debug("AT91: PM - bogus suspend state %d\n", state);
		goto error;
	}

error:
#ifdef CONFIG_PINCTRL_AT91
	at91_pinctrl_gpio_resume();
#endif
	return 0;
}