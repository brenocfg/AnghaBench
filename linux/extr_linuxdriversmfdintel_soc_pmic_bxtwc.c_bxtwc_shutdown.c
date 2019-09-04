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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_soc_pmic {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct intel_soc_pmic* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxtwc_shutdown(struct platform_device *pdev)
{
	struct intel_soc_pmic *pmic = dev_get_drvdata(&pdev->dev);

	disable_irq(pmic->irq);
}