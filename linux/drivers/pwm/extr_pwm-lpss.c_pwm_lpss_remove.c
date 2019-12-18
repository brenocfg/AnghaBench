#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * pwms; } ;
struct pwm_lpss_chip {TYPE_2__ chip; TYPE_1__* info; } ;
struct TYPE_3__ {int npwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 scalar_t__ pwm_is_enabled (int /*<<< orphan*/ *) ; 
 int pwmchip_remove (TYPE_2__*) ; 

int pwm_lpss_remove(struct pwm_lpss_chip *lpwm)
{
	int i;

	for (i = 0; i < lpwm->info->npwm; i++) {
		if (pwm_is_enabled(&lpwm->chip.pwms[i]))
			pm_runtime_put(lpwm->chip.dev);
	}
	return pwmchip_remove(&lpwm->chip);
}