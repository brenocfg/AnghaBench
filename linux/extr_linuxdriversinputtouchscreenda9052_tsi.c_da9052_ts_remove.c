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
struct da9052_tsi {int /*<<< orphan*/  dev; int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_IRQ_PENDOWN ; 
 int /*<<< orphan*/  DA9052_IRQ_TSIREADY ; 
 int /*<<< orphan*/  DA9052_LDO9_REG ; 
 int /*<<< orphan*/  da9052_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct da9052_tsi*) ; 
 int /*<<< orphan*/  da9052_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct da9052_tsi*) ; 
 struct da9052_tsi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int  da9052_ts_remove(struct platform_device *pdev)
{
	struct da9052_tsi *tsi = platform_get_drvdata(pdev);

	da9052_reg_write(tsi->da9052, DA9052_LDO9_REG, 0x19);

	da9052_free_irq(tsi->da9052, DA9052_IRQ_TSIREADY, tsi);
	da9052_free_irq(tsi->da9052, DA9052_IRQ_PENDOWN, tsi);

	input_unregister_device(tsi->dev);
	kfree(tsi);

	return 0;
}