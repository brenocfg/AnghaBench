#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tegra_soctherm {scalar_t__ thermal_irq; scalar_t__ edp_irq; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  TEGRA_SOC_OC_IRQ_MAX ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 char* dev_name (TYPE_1__*) ; 
 int devm_request_threaded_irq (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct tegra_soctherm*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  soctherm_edp_isr ; 
 int /*<<< orphan*/  soctherm_edp_isr_thread ; 
 int soctherm_oc_int_init (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soctherm_thermal_isr ; 
 int /*<<< orphan*/  soctherm_thermal_isr_thread ; 

__attribute__((used)) static int soctherm_interrupts_init(struct platform_device *pdev,
				    struct tegra_soctherm *tegra)
{
	struct device_node *np = pdev->dev.of_node;
	int ret;

	ret = soctherm_oc_int_init(np, TEGRA_SOC_OC_IRQ_MAX);
	if (ret < 0) {
		dev_err(&pdev->dev, "soctherm_oc_int_init failed\n");
		return ret;
	}

	tegra->thermal_irq = platform_get_irq(pdev, 0);
	if (tegra->thermal_irq < 0) {
		dev_dbg(&pdev->dev, "get 'thermal_irq' failed.\n");
		return 0;
	}

	tegra->edp_irq = platform_get_irq(pdev, 1);
	if (tegra->edp_irq < 0) {
		dev_dbg(&pdev->dev, "get 'edp_irq' failed.\n");
		return 0;
	}

	ret = devm_request_threaded_irq(&pdev->dev,
					tegra->thermal_irq,
					soctherm_thermal_isr,
					soctherm_thermal_isr_thread,
					IRQF_ONESHOT,
					dev_name(&pdev->dev),
					tegra);
	if (ret < 0) {
		dev_err(&pdev->dev, "request_irq 'thermal_irq' failed.\n");
		return ret;
	}

	ret = devm_request_threaded_irq(&pdev->dev,
					tegra->edp_irq,
					soctherm_edp_isr,
					soctherm_edp_isr_thread,
					IRQF_ONESHOT,
					"soctherm_edp",
					tegra);
	if (ret < 0) {
		dev_err(&pdev->dev, "request_irq 'edp_irq' failed.\n");
		return ret;
	}

	return 0;
}