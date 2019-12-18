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
struct msm_vibrator {int enabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  clk; int /*<<< orphan*/  vcc; int /*<<< orphan*/  enable_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_vibrator_stop(struct msm_vibrator *vibrator)
{
	mutex_lock(&vibrator->mutex);

	if (vibrator->enabled) {
		gpiod_set_value_cansleep(vibrator->enable_gpio, 0);
		regulator_disable(vibrator->vcc);
		clk_disable(vibrator->clk);
		vibrator->enabled = false;
	}

	mutex_unlock(&vibrator->mutex);
}