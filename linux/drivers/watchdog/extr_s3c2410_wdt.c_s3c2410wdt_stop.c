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
struct s3c2410_wdt {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __s3c2410wdt_stop (struct s3c2410_wdt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct s3c2410_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int s3c2410wdt_stop(struct watchdog_device *wdd)
{
	struct s3c2410_wdt *wdt = watchdog_get_drvdata(wdd);

	spin_lock(&wdt->lock);
	__s3c2410wdt_stop(wdt);
	spin_unlock(&wdt->lock);

	return 0;
}