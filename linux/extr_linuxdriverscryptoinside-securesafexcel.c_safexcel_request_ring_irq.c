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
struct safexcel_ring_irq_data {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_ring_irq_data*) ; 
 int platform_get_irq_byname (struct platform_device*,char const*) ; 

__attribute__((used)) static int safexcel_request_ring_irq(struct platform_device *pdev, const char *name,
				     irq_handler_t handler,
				     irq_handler_t threaded_handler,
				     struct safexcel_ring_irq_data *ring_irq_priv)
{
	int ret, irq = platform_get_irq_byname(pdev, name);

	if (irq < 0) {
		dev_err(&pdev->dev, "unable to get IRQ '%s'\n", name);
		return irq;
	}

	ret = devm_request_threaded_irq(&pdev->dev, irq, handler,
					threaded_handler, IRQF_ONESHOT,
					dev_name(&pdev->dev), ring_irq_priv);
	if (ret) {
		dev_err(&pdev->dev, "unable to request IRQ %d\n", irq);
		return ret;
	}

	return irq;
}