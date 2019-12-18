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
 int EBUSY ; 
 int /*<<< orphan*/  WATCHDOG_NAME ; 
 int /*<<< orphan*/  WDT_EFER ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_muxed_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_cfg_enter ; 
 int /*<<< orphan*/  wdt_io ; 

__attribute__((used)) static int superio_enter(void)
{
	if (!request_muxed_region(wdt_io, 2, WATCHDOG_NAME))
		return -EBUSY;

	outb_p(wdt_cfg_enter, WDT_EFER); /* Enter extended function mode */
	outb_p(wdt_cfg_enter, WDT_EFER); /* Again according to manual */

	return 0;
}