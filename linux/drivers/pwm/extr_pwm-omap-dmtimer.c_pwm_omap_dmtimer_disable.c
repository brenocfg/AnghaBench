#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pwm_omap_dmtimer_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dm_timer; TYPE_1__* pdata; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct pwm_omap_dmtimer_chip* to_pwm_omap_dmtimer_chip (struct pwm_chip*) ; 

__attribute__((used)) static void pwm_omap_dmtimer_disable(struct pwm_chip *chip,
				     struct pwm_device *pwm)
{
	struct pwm_omap_dmtimer_chip *omap = to_pwm_omap_dmtimer_chip(chip);

	mutex_lock(&omap->mutex);
	omap->pdata->stop(omap->dm_timer);
	mutex_unlock(&omap->mutex);
}