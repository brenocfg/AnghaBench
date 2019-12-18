#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  polled; } ;
struct tegra_output {int hpd_irq; int /*<<< orphan*/  cec; TYPE_2__* dev; TYPE_1__ connector; int /*<<< orphan*/ * hpd_gpio; scalar_t__ of_node; int /*<<< orphan*/  ddc; int /*<<< orphan*/  edid; int /*<<< orphan*/ * panel; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 unsigned long IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_notifier_get (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,...) ; 
 int /*<<< orphan*/ * devm_gpiod_get_from_of_node (TYPE_2__*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int gpiod_to_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpd_irq ; 
 int /*<<< orphan*/ * of_drm_find_panel (struct device_node*) ; 
 int /*<<< orphan*/  of_find_i2c_adapter_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_get_property (scalar_t__,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,char*,struct tegra_output*) ; 

int tegra_output_probe(struct tegra_output *output)
{
	struct device_node *ddc, *panel;
	unsigned long flags;
	int err, size;

	if (!output->of_node)
		output->of_node = output->dev->of_node;

	panel = of_parse_phandle(output->of_node, "nvidia,panel", 0);
	if (panel) {
		output->panel = of_drm_find_panel(panel);
		if (IS_ERR(output->panel))
			return PTR_ERR(output->panel);

		of_node_put(panel);
	}

	output->edid = of_get_property(output->of_node, "nvidia,edid", &size);

	ddc = of_parse_phandle(output->of_node, "nvidia,ddc-i2c-bus", 0);
	if (ddc) {
		output->ddc = of_find_i2c_adapter_by_node(ddc);
		if (!output->ddc) {
			err = -EPROBE_DEFER;
			of_node_put(ddc);
			return err;
		}

		of_node_put(ddc);
	}

	output->hpd_gpio = devm_gpiod_get_from_of_node(output->dev,
						       output->of_node,
						       "nvidia,hpd-gpio", 0,
						       GPIOD_IN,
						       "HDMI hotplug detect");
	if (IS_ERR(output->hpd_gpio)) {
		if (PTR_ERR(output->hpd_gpio) != -ENOENT)
			return PTR_ERR(output->hpd_gpio);

		output->hpd_gpio = NULL;
	}

	if (output->hpd_gpio) {
		err = gpiod_to_irq(output->hpd_gpio);
		if (err < 0) {
			dev_err(output->dev, "gpiod_to_irq(): %d\n", err);
			return err;
		}

		output->hpd_irq = err;

		flags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			IRQF_ONESHOT;

		err = request_threaded_irq(output->hpd_irq, NULL, hpd_irq,
					   flags, "hpd", output);
		if (err < 0) {
			dev_err(output->dev, "failed to request IRQ#%u: %d\n",
				output->hpd_irq, err);
			return err;
		}

		output->connector.polled = DRM_CONNECTOR_POLL_HPD;

		/*
		 * Disable the interrupt until the connector has been
		 * initialized to avoid a race in the hotplug interrupt
		 * handler.
		 */
		disable_irq(output->hpd_irq);
	}

	output->cec = cec_notifier_get(output->dev);
	if (!output->cec)
		return -ENOMEM;

	return 0;
}