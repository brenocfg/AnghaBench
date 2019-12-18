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
struct pwm_lpss_chip {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct pwm_lpss_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int pwm_lpss_remove (struct pwm_lpss_chip*) ; 

__attribute__((used)) static int pwm_lpss_remove_platform(struct platform_device *pdev)
{
	struct pwm_lpss_chip *lpwm = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);
	return pwm_lpss_remove(lpwm);
}