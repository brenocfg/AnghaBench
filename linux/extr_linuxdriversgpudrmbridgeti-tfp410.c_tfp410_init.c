#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ of_node; int /*<<< orphan*/ * funcs; } ;
struct tfp410 {scalar_t__ hpd; int /*<<< orphan*/  ddc; TYPE_1__ bridge; int /*<<< orphan*/  hpd_work; struct device* dev; } ;
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct tfp410*) ; 
 struct tfp410* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct tfp410*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_1__*) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_to_irq (scalar_t__) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfp410_bridge_funcs ; 
 int tfp410_get_connector_properties (struct tfp410*) ; 
 int /*<<< orphan*/  tfp410_hpd_irq_thread ; 
 int /*<<< orphan*/  tfp410_hpd_work_func ; 

__attribute__((used)) static int tfp410_init(struct device *dev)
{
	struct tfp410 *dvi;
	int ret;

	if (!dev->of_node) {
		dev_err(dev, "device-tree data is missing\n");
		return -ENXIO;
	}

	dvi = devm_kzalloc(dev, sizeof(*dvi), GFP_KERNEL);
	if (!dvi)
		return -ENOMEM;
	dev_set_drvdata(dev, dvi);

	dvi->bridge.funcs = &tfp410_bridge_funcs;
	dvi->bridge.of_node = dev->of_node;
	dvi->dev = dev;

	ret = tfp410_get_connector_properties(dvi);
	if (ret)
		goto fail;

	if (dvi->hpd) {
		INIT_DELAYED_WORK(&dvi->hpd_work, tfp410_hpd_work_func);

		ret = devm_request_threaded_irq(dev, gpiod_to_irq(dvi->hpd),
			NULL, tfp410_hpd_irq_thread, IRQF_TRIGGER_RISING |
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			"hdmi-hpd", dvi);
		if (ret) {
			DRM_ERROR("failed to register hpd interrupt\n");
			goto fail;
		}
	}

	drm_bridge_add(&dvi->bridge);

	return 0;
fail:
	i2c_put_adapter(dvi->ddc);
	if (dvi->hpd)
		gpiod_put(dvi->hpd);
	return ret;
}