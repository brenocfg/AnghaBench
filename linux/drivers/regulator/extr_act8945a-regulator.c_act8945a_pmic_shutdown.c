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
struct act8945a_pmic {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT8945A_SYS_CTRL ; 
 struct act8945a_pmic* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void act8945a_pmic_shutdown(struct platform_device *pdev)
{
	struct act8945a_pmic *act8945a = platform_get_drvdata(pdev);

	/*
	 * Ask the PMIC to shutdown everything on the next PWRHLD transition.
	 */
	regmap_write(act8945a->regmap, ACT8945A_SYS_CTRL, 0x0);
}