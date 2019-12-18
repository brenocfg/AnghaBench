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
typedef  int u32 ;
struct titsc {int coordinate_readouts; int /*<<< orphan*/  input; int /*<<< orphan*/  mfd_tscadc; int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  am335x_tsc_se_clr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct titsc*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct titsc*) ; 
 struct titsc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int titsc_remove(struct platform_device *pdev)
{
	struct titsc *ts_dev = platform_get_drvdata(pdev);
	u32 steps;

	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);
	free_irq(ts_dev->irq, ts_dev);

	/* total steps followed by the enable mask */
	steps = 2 * ts_dev->coordinate_readouts + 2;
	steps = (1 << steps) - 1;
	am335x_tsc_se_clr(ts_dev->mfd_tscadc, steps);

	input_unregister_device(ts_dev->input);

	kfree(ts_dev);
	return 0;
}