#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_23__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_25__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_28__ {TYPE_1__* dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; int /*<<< orphan*/  wrapper; } ;
struct TYPE_26__ {int /*<<< orphan*/  of_node; TYPE_1__* parent; } ;
struct TYPE_27__ {int /*<<< orphan*/  name; TYPE_23__ dev; int /*<<< orphan*/ * algo; } ;
struct geni_i2c_dev {int irq; int tx_wm; int suspended; TYPE_9__ se; TYPE_6__ adap; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; int /*<<< orphan*/  clk_freq_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (TYPE_1__*) ; 
 int /*<<< orphan*/  ACPI_COMPANION_SET (TYPE_23__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int GENI_SE_I2C ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_AUTO_SUSPEND_DELAY ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KHZ (int) ; 
 int /*<<< orphan*/  PACKING_BYTES_PW ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int device_property_read_u32 (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct geni_i2c_dev* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct geni_i2c_dev*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  geni_i2c_algo ; 
 int geni_i2c_clk_map_idx (struct geni_i2c_dev*) ; 
 int /*<<< orphan*/  geni_i2c_irq ; 
 int /*<<< orphan*/  geni_se_config_packing (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int geni_se_get_tx_fifo_depth (TYPE_9__*) ; 
 int /*<<< orphan*/  geni_se_init (TYPE_9__*,int,int) ; 
 int geni_se_read_proto (TYPE_9__*) ; 
 int geni_se_resources_off (TYPE_9__*) ; 
 int geni_se_resources_on (TYPE_9__*) ; 
 scalar_t__ has_acpi_companion (TYPE_1__*) ; 
 int i2c_add_adapter (TYPE_6__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_6__*,struct geni_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct geni_i2c_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int geni_i2c_probe(struct platform_device *pdev)
{
	struct geni_i2c_dev *gi2c;
	struct resource *res;
	u32 proto, tx_depth;
	int ret;

	gi2c = devm_kzalloc(&pdev->dev, sizeof(*gi2c), GFP_KERNEL);
	if (!gi2c)
		return -ENOMEM;

	gi2c->se.dev = &pdev->dev;
	gi2c->se.wrapper = dev_get_drvdata(pdev->dev.parent);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gi2c->se.base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gi2c->se.base))
		return PTR_ERR(gi2c->se.base);

	gi2c->se.clk = devm_clk_get(&pdev->dev, "se");
	if (IS_ERR(gi2c->se.clk) && !has_acpi_companion(&pdev->dev)) {
		ret = PTR_ERR(gi2c->se.clk);
		dev_err(&pdev->dev, "Err getting SE Core clk %d\n", ret);
		return ret;
	}

	ret = device_property_read_u32(&pdev->dev, "clock-frequency",
							&gi2c->clk_freq_out);
	if (ret) {
		dev_info(&pdev->dev,
			"Bus frequency not specified, default to 100kHz.\n");
		gi2c->clk_freq_out = KHZ(100);
	}

	if (has_acpi_companion(&pdev->dev))
		ACPI_COMPANION_SET(&gi2c->adap.dev, ACPI_COMPANION(&pdev->dev));

	gi2c->irq = platform_get_irq(pdev, 0);
	if (gi2c->irq < 0) {
		dev_err(&pdev->dev, "IRQ error for i2c-geni\n");
		return gi2c->irq;
	}

	ret = geni_i2c_clk_map_idx(gi2c);
	if (ret) {
		dev_err(&pdev->dev, "Invalid clk frequency %d Hz: %d\n",
			gi2c->clk_freq_out, ret);
		return ret;
	}

	gi2c->adap.algo = &geni_i2c_algo;
	init_completion(&gi2c->done);
	spin_lock_init(&gi2c->lock);
	platform_set_drvdata(pdev, gi2c);
	ret = devm_request_irq(&pdev->dev, gi2c->irq, geni_i2c_irq,
			       IRQF_TRIGGER_HIGH, "i2c_geni", gi2c);
	if (ret) {
		dev_err(&pdev->dev, "Request_irq failed:%d: err:%d\n",
			gi2c->irq, ret);
		return ret;
	}
	/* Disable the interrupt so that the system can enter low-power mode */
	disable_irq(gi2c->irq);
	i2c_set_adapdata(&gi2c->adap, gi2c);
	gi2c->adap.dev.parent = &pdev->dev;
	gi2c->adap.dev.of_node = pdev->dev.of_node;
	strlcpy(gi2c->adap.name, "Geni-I2C", sizeof(gi2c->adap.name));

	ret = geni_se_resources_on(&gi2c->se);
	if (ret) {
		dev_err(&pdev->dev, "Error turning on resources %d\n", ret);
		return ret;
	}
	proto = geni_se_read_proto(&gi2c->se);
	tx_depth = geni_se_get_tx_fifo_depth(&gi2c->se);
	if (proto != GENI_SE_I2C) {
		dev_err(&pdev->dev, "Invalid proto %d\n", proto);
		geni_se_resources_off(&gi2c->se);
		return -ENXIO;
	}
	gi2c->tx_wm = tx_depth - 1;
	geni_se_init(&gi2c->se, gi2c->tx_wm, tx_depth);
	geni_se_config_packing(&gi2c->se, BITS_PER_BYTE, PACKING_BYTES_PW,
							true, true, true);
	ret = geni_se_resources_off(&gi2c->se);
	if (ret) {
		dev_err(&pdev->dev, "Error turning off resources %d\n", ret);
		return ret;
	}

	dev_dbg(&pdev->dev, "i2c fifo/se-dma mode. fifo depth:%d\n", tx_depth);

	gi2c->suspended = 1;
	pm_runtime_set_suspended(gi2c->se.dev);
	pm_runtime_set_autosuspend_delay(gi2c->se.dev, I2C_AUTO_SUSPEND_DELAY);
	pm_runtime_use_autosuspend(gi2c->se.dev);
	pm_runtime_enable(gi2c->se.dev);

	ret = i2c_add_adapter(&gi2c->adap);
	if (ret) {
		dev_err(&pdev->dev, "Error adding i2c adapter %d\n", ret);
		pm_runtime_disable(gi2c->se.dev);
		return ret;
	}

	dev_dbg(&pdev->dev, "Geni-I2C adaptor successfully added\n");

	return 0;
}