#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;
struct hdmi_context {int /*<<< orphan*/  mutex; TYPE_3__* ddc_adpt; scalar_t__ regs_hdmiphy; TYPE_2__* hdmiphy_port; int /*<<< orphan*/  reg_hdmi_en; int /*<<< orphan*/  notifier; TYPE_1__ audio; int /*<<< orphan*/  hotplug_work; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_notifier_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_component_ops ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct hdmi_context* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_remove(struct platform_device *pdev)
{
	struct hdmi_context *hdata = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&hdata->hotplug_work);
	cec_notifier_set_phys_addr(hdata->notifier, CEC_PHYS_ADDR_INVALID);

	component_del(&pdev->dev, &hdmi_component_ops);
	platform_device_unregister(hdata->audio.pdev);

	cec_notifier_put(hdata->notifier);
	pm_runtime_disable(&pdev->dev);

	if (!IS_ERR(hdata->reg_hdmi_en))
		regulator_disable(hdata->reg_hdmi_en);

	if (hdata->hdmiphy_port)
		put_device(&hdata->hdmiphy_port->dev);

	if (hdata->regs_hdmiphy)
		iounmap(hdata->regs_hdmiphy);

	put_device(&hdata->ddc_adpt->dev);

	mutex_destroy(&hdata->mutex);

	return 0;
}