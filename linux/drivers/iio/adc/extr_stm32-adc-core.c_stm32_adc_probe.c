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
struct stm32_adc_priv_cfg {int (* clk_sel ) (struct platform_device*,struct stm32_adc_priv*) ;} ;
struct TYPE_5__ {int vref_mv; int /*<<< orphan*/  phys_base; int /*<<< orphan*/ * base; } ;
struct stm32_adc_priv {struct stm32_adc_priv_cfg const* cfg; TYPE_2__ common; int /*<<< orphan*/ * vref; int /*<<< orphan*/ * bclk; int /*<<< orphan*/ * aclk; int /*<<< orphan*/ * vdda; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {TYPE_1__* driver; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STM32_ADC_CORE_SLEEP_DELAY_MS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct stm32_adc_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 TYPE_3__* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ *) ; 
 int stm32_adc_core_hw_start (struct device*) ; 
 int /*<<< orphan*/  stm32_adc_core_hw_stop (struct device*) ; 
 int stm32_adc_core_switches_probe (struct device*,struct stm32_adc_priv*) ; 
 int stm32_adc_irq_probe (struct platform_device*,struct stm32_adc_priv*) ; 
 int /*<<< orphan*/  stm32_adc_irq_remove (struct platform_device*,struct stm32_adc_priv*) ; 
 int stub1 (struct platform_device*,struct stm32_adc_priv*) ; 

__attribute__((used)) static int stm32_adc_probe(struct platform_device *pdev)
{
	struct stm32_adc_priv *priv;
	struct device *dev = &pdev->dev;
	struct device_node *np = pdev->dev.of_node;
	struct resource *res;
	int ret;

	if (!pdev->dev.of_node)
		return -ENODEV;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	platform_set_drvdata(pdev, &priv->common);

	priv->cfg = (const struct stm32_adc_priv_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->common.base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->common.base))
		return PTR_ERR(priv->common.base);
	priv->common.phys_base = res->start;

	priv->vdda = devm_regulator_get(&pdev->dev, "vdda");
	if (IS_ERR(priv->vdda)) {
		ret = PTR_ERR(priv->vdda);
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "vdda get failed, %d\n", ret);
		return ret;
	}

	priv->vref = devm_regulator_get(&pdev->dev, "vref");
	if (IS_ERR(priv->vref)) {
		ret = PTR_ERR(priv->vref);
		dev_err(&pdev->dev, "vref get failed, %d\n", ret);
		return ret;
	}

	priv->aclk = devm_clk_get(&pdev->dev, "adc");
	if (IS_ERR(priv->aclk)) {
		ret = PTR_ERR(priv->aclk);
		if (ret != -ENOENT) {
			dev_err(&pdev->dev, "Can't get 'adc' clock\n");
			return ret;
		}
		priv->aclk = NULL;
	}

	priv->bclk = devm_clk_get(&pdev->dev, "bus");
	if (IS_ERR(priv->bclk)) {
		ret = PTR_ERR(priv->bclk);
		if (ret != -ENOENT) {
			dev_err(&pdev->dev, "Can't get 'bus' clock\n");
			return ret;
		}
		priv->bclk = NULL;
	}

	ret = stm32_adc_core_switches_probe(dev, priv);
	if (ret)
		return ret;

	pm_runtime_get_noresume(dev);
	pm_runtime_set_active(dev);
	pm_runtime_set_autosuspend_delay(dev, STM32_ADC_CORE_SLEEP_DELAY_MS);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_enable(dev);

	ret = stm32_adc_core_hw_start(dev);
	if (ret)
		goto err_pm_stop;

	ret = regulator_get_voltage(priv->vref);
	if (ret < 0) {
		dev_err(&pdev->dev, "vref get voltage failed, %d\n", ret);
		goto err_hw_stop;
	}
	priv->common.vref_mv = ret / 1000;
	dev_dbg(&pdev->dev, "vref+=%dmV\n", priv->common.vref_mv);

	ret = priv->cfg->clk_sel(pdev, priv);
	if (ret < 0)
		goto err_hw_stop;

	ret = stm32_adc_irq_probe(pdev, priv);
	if (ret < 0)
		goto err_hw_stop;

	ret = of_platform_populate(np, NULL, NULL, &pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to populate DT children\n");
		goto err_irq_remove;
	}

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return 0;

err_irq_remove:
	stm32_adc_irq_remove(pdev, priv);
err_hw_stop:
	stm32_adc_core_hw_stop(dev);
err_pm_stop:
	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_put_noidle(dev);

	return ret;
}