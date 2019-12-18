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
struct mei_wdt {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 scalar_t__ __mei_wdt_is_registered (struct mei_wdt*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mei_wdt_unregister(struct mei_wdt *wdt)
{
	mutex_lock(&wdt->reg_lock);

	if (__mei_wdt_is_registered(wdt)) {
		watchdog_unregister_device(&wdt->wdd);
		watchdog_set_drvdata(&wdt->wdd, NULL);
		memset(&wdt->wdd, 0, sizeof(wdt->wdd));
	}

	mutex_unlock(&wdt->reg_lock);
}