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

/* Variables and functions */
 int /*<<< orphan*/  abx500_temp_irq_handler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct platform_device*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 

__attribute__((used)) static int setup_irqs(struct platform_device *pdev)
{
	int ret;
	int irq = platform_get_irq_byname(pdev, "ABX500_TEMP_WARM");

	if (irq < 0) {
		dev_err(&pdev->dev, "Get irq by name failed\n");
		return irq;
	}

	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL,
		abx500_temp_irq_handler, 0, "abx500-temp", pdev);
	if (ret < 0)
		dev_err(&pdev->dev, "Request threaded irq failed (%d)\n", ret);

	return ret;
}