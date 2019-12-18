#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_7__ {scalar_t__ irq; int has_gcr_regs; int /*<<< orphan*/  telemetry_dev; int /*<<< orphan*/  punit_dev; int /*<<< orphan*/  tco_dev; int /*<<< orphan*/  gcr_lock; int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  irq_mode; TYPE_2__* dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPC_TRIGGER_MODE_IRQ ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  devm_free_irq (TYPE_2__*,scalar_t__,TYPE_1__*) ; 
 scalar_t__ devm_request_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ipc_group ; 
 int /*<<< orphan*/  ioc ; 
 int ipc_create_pmc_devices () ; 
 int ipc_plat_get_res (struct platform_device*) ; 
 TYPE_1__ ipcdev ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipc_plat_probe(struct platform_device *pdev)
{
	int ret;

	ipcdev.dev = &pdev->dev;
	ipcdev.irq_mode = IPC_TRIGGER_MODE_IRQ;
	init_completion(&ipcdev.cmd_complete);
	spin_lock_init(&ipcdev.gcr_lock);

	ipcdev.irq = platform_get_irq(pdev, 0);
	if (ipcdev.irq < 0)
		return -EINVAL;

	ret = ipc_plat_get_res(pdev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request resource\n");
		return ret;
	}

	ret = ipc_create_pmc_devices();
	if (ret) {
		dev_err(&pdev->dev, "Failed to create pmc devices\n");
		return ret;
	}

	if (devm_request_irq(&pdev->dev, ipcdev.irq, ioc, IRQF_NO_SUSPEND,
			     "intel_pmc_ipc", &ipcdev)) {
		dev_err(&pdev->dev, "Failed to request irq\n");
		ret = -EBUSY;
		goto err_irq;
	}

	ret = sysfs_create_group(&pdev->dev.kobj, &intel_ipc_group);
	if (ret) {
		dev_err(&pdev->dev, "Failed to create sysfs group %d\n",
			ret);
		goto err_sys;
	}

	ipcdev.has_gcr_regs = true;

	return 0;
err_sys:
	devm_free_irq(&pdev->dev, ipcdev.irq, &ipcdev);
err_irq:
	platform_device_unregister(ipcdev.tco_dev);
	platform_device_unregister(ipcdev.punit_dev);
	platform_device_unregister(ipcdev.telemetry_dev);

	return ret;
}