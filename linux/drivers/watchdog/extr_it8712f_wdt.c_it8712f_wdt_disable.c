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
 int /*<<< orphan*/  LDN_GPIO ; 
 scalar_t__ WDT_CONFIG ; 
 scalar_t__ WDT_CONTROL ; 
 scalar_t__ WDT_TIMEOUT ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int revision ; 
 int superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 int /*<<< orphan*/  superio_outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int it8712f_wdt_disable(void)
{
	int ret = superio_enter();
	if (ret)
		return ret;

	pr_debug("disabling watchdog timer\n");
	superio_select(LDN_GPIO);

	superio_outb(0, WDT_CONFIG);
	superio_outb(0, WDT_CONTROL);
	if (revision >= 0x08)
		superio_outb(0, WDT_TIMEOUT + 1);
	superio_outb(0, WDT_TIMEOUT);

	superio_exit();
	return 0;
}