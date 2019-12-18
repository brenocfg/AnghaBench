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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83627HF_LD_WDT ; 
 int /*<<< orphan*/  cr_wdt_timeout ; 
 int superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 unsigned int superio_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int wdt_get_time(struct watchdog_device *wdog)
{
	unsigned int timeleft;
	int ret;

	ret = superio_enter();
	if (ret)
		return 0;

	superio_select(W83627HF_LD_WDT);
	timeleft = superio_inb(cr_wdt_timeout);
	superio_exit();

	return timeleft;
}