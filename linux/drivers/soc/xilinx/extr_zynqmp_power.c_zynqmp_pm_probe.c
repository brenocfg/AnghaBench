#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  attr; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* get_api_version ) (scalar_t__*) ;int /*<<< orphan*/  (* init_finalize ) () ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 scalar_t__ ZYNQMP_PM_VERSION ; 
 TYPE_7__ dev_attr_suspend_mode ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_1__* eemi_ops ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (scalar_t__*) ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* zynqmp_pm_get_eemi_ops () ; 
 int /*<<< orphan*/  zynqmp_pm_isr ; 

__attribute__((used)) static int zynqmp_pm_probe(struct platform_device *pdev)
{
	int ret, irq;
	u32 pm_api_version;

	eemi_ops = zynqmp_pm_get_eemi_ops();
	if (IS_ERR(eemi_ops))
		return PTR_ERR(eemi_ops);

	if (!eemi_ops->get_api_version || !eemi_ops->init_finalize)
		return -ENXIO;

	eemi_ops->init_finalize();
	eemi_ops->get_api_version(&pm_api_version);

	/* Check PM API version number */
	if (pm_api_version < ZYNQMP_PM_VERSION)
		return -ENODEV;

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return -ENXIO;

	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL, zynqmp_pm_isr,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					dev_name(&pdev->dev), &pdev->dev);
	if (ret) {
		dev_err(&pdev->dev, "devm_request_threaded_irq '%d' failed "
			"with %d\n", irq, ret);
		return ret;
	}

	ret = sysfs_create_file(&pdev->dev.kobj, &dev_attr_suspend_mode.attr);
	if (ret) {
		dev_err(&pdev->dev, "unable to create sysfs interface\n");
		return ret;
	}

	return 0;
}