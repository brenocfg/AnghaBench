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
 int /*<<< orphan*/  DIAG_STAT_X288 ; 
 int /*<<< orphan*/  DIAG_WDOG_BUSY ; 
 int /*<<< orphan*/  WDT_FUNC_CANCEL ; 
 int __diag288 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static int wdt_stop(struct watchdog_device *dev)
{
	int ret;

	diag_stat_inc(DIAG_STAT_X288);
	ret = __diag288(WDT_FUNC_CANCEL, 0, 0, 0);

	clear_bit(DIAG_WDOG_BUSY, &wdt_status);

	return ret;
}