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
struct scaler_data {int num_clk; int /*<<< orphan*/ * clk_name; } ;
struct scaler_context {int /*<<< orphan*/ * clock; struct scaler_data* scaler_data; int /*<<< orphan*/  regs; struct device* dev; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALER_AUTOSUSPEND_DELAY ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct scaler_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct scaler_context*) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct scaler_context*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  scaler_component_ops ; 
 int /*<<< orphan*/  scaler_irq_handler ; 

__attribute__((used)) static int scaler_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource	*regs_res;
	struct scaler_context *scaler;
	int irq;
	int ret, i;

	scaler = devm_kzalloc(dev, sizeof(*scaler), GFP_KERNEL);
	if (!scaler)
		return -ENOMEM;

	scaler->scaler_data =
		(struct scaler_data *)of_device_get_match_data(dev);

	scaler->dev = dev;
	regs_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	scaler->regs = devm_ioremap_resource(dev, regs_res);
	if (IS_ERR(scaler->regs))
		return PTR_ERR(scaler->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "failed to get irq\n");
		return irq;
	}

	ret = devm_request_threaded_irq(dev, irq, NULL,	scaler_irq_handler,
					IRQF_ONESHOT, "drm_scaler", scaler);
	if (ret < 0) {
		dev_err(dev, "failed to request irq\n");
		return ret;
	}

	for (i = 0; i < scaler->scaler_data->num_clk; ++i) {
		scaler->clock[i] = devm_clk_get(dev,
					      scaler->scaler_data->clk_name[i]);
		if (IS_ERR(scaler->clock[i])) {
			dev_err(dev, "failed to get clock\n");
			return PTR_ERR(scaler->clock[i]);
		}
	}

	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, SCALER_AUTOSUSPEND_DELAY);
	pm_runtime_enable(dev);
	platform_set_drvdata(pdev, scaler);

	ret = component_add(dev, &scaler_component_ops);
	if (ret)
		goto err_ippdrv_register;

	return 0;

err_ippdrv_register:
	pm_runtime_dont_use_autosuspend(dev);
	pm_runtime_disable(dev);
	return ret;
}