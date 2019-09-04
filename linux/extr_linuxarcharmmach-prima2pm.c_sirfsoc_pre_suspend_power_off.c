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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SIRFSOC_DEEP_SLEEP_MODE ; 
 scalar_t__ SIRFSOC_PWRC_SCRATCH_PAD1 ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_resume ; 
 scalar_t__ sirfsoc_pwrc_base ; 
 int /*<<< orphan*/  sirfsoc_rtc_iobrg_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sirfsoc_set_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirfsoc_set_wakeup_source () ; 

__attribute__((used)) static int sirfsoc_pre_suspend_power_off(void)
{
	u32 wakeup_entry = __pa_symbol(cpu_resume);

	sirfsoc_rtc_iobrg_writel(wakeup_entry, sirfsoc_pwrc_base +
		SIRFSOC_PWRC_SCRATCH_PAD1);

	sirfsoc_set_wakeup_source();

	sirfsoc_set_sleep_mode(SIRFSOC_DEEP_SLEEP_MODE);

	return 0;
}