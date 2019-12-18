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
struct tpu_pwm_device {int timer_on; TYPE_2__* tpu; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpu_pwm_start_stop (struct tpu_pwm_device*,int) ; 

__attribute__((used)) static void tpu_pwm_timer_stop(struct tpu_pwm_device *pwm)
{
	if (!pwm->timer_on)
		return;

	/* Disable channel. */
	tpu_pwm_start_stop(pwm, false);

	/* Stop clock and mark device as idle. */
	clk_disable_unprepare(pwm->tpu->clk);
	pm_runtime_put(&pwm->tpu->pdev->dev);

	pwm->timer_on = false;
}