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
struct watchdog_device {unsigned int timeout; } ;
struct uniphier_wdt_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int __uniphier_watchdog_restart (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 
 struct uniphier_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int uniphier_watchdog_set_timeout(struct watchdog_device *w,
					 unsigned int t)
{
	struct uniphier_wdt_dev *wdev = watchdog_get_drvdata(w);
	unsigned int tmp_timeout;
	int ret;

	tmp_timeout = roundup_pow_of_two(t);
	if (tmp_timeout == w->timeout)
		return 0;

	if (watchdog_active(w)) {
		ret = __uniphier_watchdog_restart(wdev->regmap, tmp_timeout);
		if (ret)
			return ret;
	}

	w->timeout = tmp_timeout;

	return 0;
}