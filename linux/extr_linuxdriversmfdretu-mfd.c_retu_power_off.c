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
struct retu_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETU_REG_CC1 ; 
 int /*<<< orphan*/  RETU_REG_WATCHDOG ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct retu_dev* retu_pm_power_off ; 

__attribute__((used)) static void retu_power_off(void)
{
	struct retu_dev *rdev = retu_pm_power_off;
	int reg;

	mutex_lock(&retu_pm_power_off->mutex);

	/* Ignore power button state */
	regmap_read(rdev->regmap, RETU_REG_CC1, &reg);
	regmap_write(rdev->regmap, RETU_REG_CC1, reg | 2);

	/* Expire watchdog immediately */
	regmap_write(rdev->regmap, RETU_REG_WATCHDOG, 0);

	/* Wait for poweroff */
	for (;;)
		cpu_relax();

	mutex_unlock(&retu_pm_power_off->mutex);
}