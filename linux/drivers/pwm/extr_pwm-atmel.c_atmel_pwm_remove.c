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
struct platform_device {int dummy; } ;
struct atmel_pwm_chip {int /*<<< orphan*/  chip; int /*<<< orphan*/  isr_lock; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct atmel_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_pwm_remove(struct platform_device *pdev)
{
	struct atmel_pwm_chip *atmel_pwm = platform_get_drvdata(pdev);

	clk_unprepare(atmel_pwm->clk);
	mutex_destroy(&atmel_pwm->isr_lock);

	return pwmchip_remove(&atmel_pwm->chip);
}