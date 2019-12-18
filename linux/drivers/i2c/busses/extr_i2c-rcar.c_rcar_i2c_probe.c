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
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct i2c_adapter {int retries; int /*<<< orphan*/  name; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * bus_recovery_info; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/ * algo; int /*<<< orphan*/  nr; } ;
struct rcar_i2c_priv {int devtype; int /*<<< orphan*/  irq; int /*<<< orphan*/  flags; void* rstc; void* dma_tx; void* dma_rx; int /*<<< orphan*/  dma_direction; int /*<<< orphan*/  sg; struct i2c_adapter adap; int /*<<< orphan*/  wait; void* io; int /*<<< orphan*/  res; void* clk; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct i2c_timings {int dummy; } ;
typedef  enum rcar_i2c_type { ____Placeholder_rcar_i2c_type } rcar_i2c_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON_MSG (int,char*) ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENOTSUPP ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 scalar_t__ I2C_RCAR_GEN3 ; 
 int /*<<< orphan*/  ID_P_PM_BLOCKED ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int RCAR_MIN_DMA_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (struct device*,int /*<<< orphan*/ ) ; 
 struct rcar_i2c_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rcar_i2c_priv*) ; 
 void* devm_reset_control_get_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_parse_fw_timings (struct device*,struct i2c_timings*,int) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct rcar_i2c_priv*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_i2c_priv*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  rcar_i2c_algo ; 
 int /*<<< orphan*/  rcar_i2c_bri ; 
 int rcar_i2c_clock_calculate (struct rcar_i2c_priv*,struct i2c_timings*) ; 
 int /*<<< orphan*/  rcar_i2c_irq ; 
 int /*<<< orphan*/  rcar_i2c_quirks ; 
 int reset_control_status (void*) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rcar_i2c_probe(struct platform_device *pdev)
{
	struct rcar_i2c_priv *priv;
	struct i2c_adapter *adap;
	struct device *dev = &pdev->dev;
	struct i2c_timings i2c_t;
	int ret;

	/* Otherwise logic will break because some bytes must always use PIO */
	BUILD_BUG_ON_MSG(RCAR_MIN_DMA_LEN < 3, "Invalid min DMA length");

	priv = devm_kzalloc(dev, sizeof(struct rcar_i2c_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(dev, "cannot get clock\n");
		return PTR_ERR(priv->clk);
	}

	priv->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	priv->io = devm_ioremap_resource(dev, priv->res);
	if (IS_ERR(priv->io))
		return PTR_ERR(priv->io);

	priv->devtype = (enum rcar_i2c_type)of_device_get_match_data(dev);
	init_waitqueue_head(&priv->wait);

	adap = &priv->adap;
	adap->nr = pdev->id;
	adap->algo = &rcar_i2c_algo;
	adap->class = I2C_CLASS_DEPRECATED;
	adap->retries = 3;
	adap->dev.parent = dev;
	adap->dev.of_node = dev->of_node;
	adap->bus_recovery_info = &rcar_i2c_bri;
	adap->quirks = &rcar_i2c_quirks;
	i2c_set_adapdata(adap, priv);
	strlcpy(adap->name, pdev->name, sizeof(adap->name));

	i2c_parse_fw_timings(dev, &i2c_t, false);

	/* Init DMA */
	sg_init_table(&priv->sg, 1);
	priv->dma_direction = DMA_NONE;
	priv->dma_rx = priv->dma_tx = ERR_PTR(-EPROBE_DEFER);

	/* Activate device for clock calculation */
	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);
	ret = rcar_i2c_clock_calculate(priv, &i2c_t);
	if (ret < 0)
		goto out_pm_put;

	if (priv->devtype == I2C_RCAR_GEN3) {
		priv->rstc = devm_reset_control_get_exclusive(&pdev->dev, NULL);
		if (!IS_ERR(priv->rstc)) {
			ret = reset_control_status(priv->rstc);
			if (ret < 0)
				priv->rstc = ERR_PTR(-ENOTSUPP);
		}
	}

	/* Stay always active when multi-master to keep arbitration working */
	if (of_property_read_bool(dev->of_node, "multi-master"))
		priv->flags |= ID_P_PM_BLOCKED;
	else
		pm_runtime_put(dev);


	priv->irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(dev, priv->irq, rcar_i2c_irq, 0, dev_name(dev), priv);
	if (ret < 0) {
		dev_err(dev, "cannot get irq %d\n", priv->irq);
		goto out_pm_disable;
	}

	platform_set_drvdata(pdev, priv);

	ret = i2c_add_numbered_adapter(adap);
	if (ret < 0)
		goto out_pm_disable;

	dev_info(dev, "probed\n");

	return 0;

 out_pm_put:
	pm_runtime_put(dev);
 out_pm_disable:
	pm_runtime_disable(dev);
	return ret;
}