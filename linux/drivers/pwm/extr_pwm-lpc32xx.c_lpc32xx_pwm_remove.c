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
struct platform_device {int dummy; } ;
struct TYPE_2__ {unsigned int npwm; int /*<<< orphan*/ * pwms; } ;
struct lpc32xx_pwm_chip {TYPE_1__ chip; } ;

/* Variables and functions */
 struct lpc32xx_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ *) ; 
 int pwmchip_remove (TYPE_1__*) ; 

__attribute__((used)) static int lpc32xx_pwm_remove(struct platform_device *pdev)
{
	struct lpc32xx_pwm_chip *lpc32xx = platform_get_drvdata(pdev);
	unsigned int i;

	for (i = 0; i < lpc32xx->chip.npwm; i++)
		pwm_disable(&lpc32xx->chip.pwms[i]);

	return pwmchip_remove(&lpc32xx->chip);
}