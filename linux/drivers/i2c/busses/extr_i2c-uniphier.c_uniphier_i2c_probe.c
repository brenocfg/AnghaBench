#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/ * bus_recovery_info; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct uniphier_i2c_priv {unsigned long clk_cycle; int /*<<< orphan*/  clk; TYPE_2__ adap; int /*<<< orphan*/  comp; int /*<<< orphan*/  membase; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 unsigned long UNIPHIER_I2C_DEFAULT_SPEED ; 
 unsigned long UNIPHIER_I2C_MAX_SPEED ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct uniphier_i2c_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uniphier_i2c_priv*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct uniphier_i2c_priv*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned long*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uniphier_i2c_priv*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uniphier_i2c_algo ; 
 int /*<<< orphan*/  uniphier_i2c_bus_recovery_info ; 
 int /*<<< orphan*/  uniphier_i2c_hw_init (struct uniphier_i2c_priv*) ; 
 int /*<<< orphan*/  uniphier_i2c_interrupt ; 

__attribute__((used)) static int uniphier_i2c_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uniphier_i2c_priv *priv;
	u32 bus_speed;
	unsigned long clk_rate;
	int irq, ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->membase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->membase))
		return PTR_ERR(priv->membase);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "failed to get IRQ number\n");
		return irq;
	}

	if (of_property_read_u32(dev->of_node, "clock-frequency", &bus_speed))
		bus_speed = UNIPHIER_I2C_DEFAULT_SPEED;

	if (!bus_speed || bus_speed > UNIPHIER_I2C_MAX_SPEED) {
		dev_err(dev, "invalid clock-frequency %d\n", bus_speed);
		return -EINVAL;
	}

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(dev, "failed to get clock\n");
		return PTR_ERR(priv->clk);
	}

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		return ret;

	clk_rate = clk_get_rate(priv->clk);
	if (!clk_rate) {
		dev_err(dev, "input clock rate should not be zero\n");
		ret = -EINVAL;
		goto disable_clk;
	}

	priv->clk_cycle = clk_rate / bus_speed;
	init_completion(&priv->comp);
	priv->adap.owner = THIS_MODULE;
	priv->adap.algo = &uniphier_i2c_algo;
	priv->adap.dev.parent = dev;
	priv->adap.dev.of_node = dev->of_node;
	strlcpy(priv->adap.name, "UniPhier I2C", sizeof(priv->adap.name));
	priv->adap.bus_recovery_info = &uniphier_i2c_bus_recovery_info;
	i2c_set_adapdata(&priv->adap, priv);
	platform_set_drvdata(pdev, priv);

	uniphier_i2c_hw_init(priv);

	ret = devm_request_irq(dev, irq, uniphier_i2c_interrupt, 0, pdev->name,
			       priv);
	if (ret) {
		dev_err(dev, "failed to request irq %d\n", irq);
		goto disable_clk;
	}

	ret = i2c_add_adapter(&priv->adap);
disable_clk:
	if (ret)
		clk_disable_unprepare(priv->clk);

	return ret;
}