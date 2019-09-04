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
struct int3496_data {int /*<<< orphan*/  work; int /*<<< orphan*/  usb_id_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct int3496_data*) ; 
 struct int3496_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int int3496_remove(struct platform_device *pdev)
{
	struct int3496_data *data = platform_get_drvdata(pdev);

	devm_free_irq(&pdev->dev, data->usb_id_irq, data);
	cancel_delayed_work_sync(&data->work);

	return 0;
}