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
struct mei_wdt {int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  watchdog_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool __mei_wdt_is_registered(struct mei_wdt *wdt)
{
	return !!watchdog_get_drvdata(&wdt->wdd);
}