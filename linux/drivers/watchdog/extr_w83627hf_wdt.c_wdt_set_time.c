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
 int /*<<< orphan*/  W83627HF_LD_WDT ; 
 int /*<<< orphan*/  cr_wdt_timeout ; 
 int superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 int /*<<< orphan*/  superio_outb (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wdt_set_time(unsigned int timeout)
{
	int ret;

	ret = superio_enter();
	if (ret)
		return ret;

	superio_select(W83627HF_LD_WDT);
	superio_outb(cr_wdt_timeout, timeout);
	superio_exit();

	return 0;
}