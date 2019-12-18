#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  of_node; TYPE_4__* parent; } ;
struct TYPE_12__ {int nr; int /*<<< orphan*/  name; TYPE_9__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/ * algo; } ;
struct TYPE_11__ {scalar_t__ irq; } ;
struct xlp9xx_i2c_dev {scalar_t__ irq; TYPE_2__ adapter; TYPE_4__* dev; int /*<<< orphan*/  msg_complete; TYPE_1__ alert_data; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_COMPANION_SET (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct xlp9xx_i2c_dev* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xlp9xx_i2c_dev*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct xlp9xx_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xlp9xx_i2c_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  xlp9xx_i2c_algo ; 
 int /*<<< orphan*/  xlp9xx_i2c_get_frequency (struct platform_device*,struct xlp9xx_i2c_dev*) ; 
 int /*<<< orphan*/  xlp9xx_i2c_init (struct xlp9xx_i2c_dev*) ; 
 int /*<<< orphan*/  xlp9xx_i2c_isr ; 
 int xlp9xx_i2c_smbus_setup (struct xlp9xx_i2c_dev*,struct platform_device*) ; 

__attribute__((used)) static int xlp9xx_i2c_probe(struct platform_device *pdev)
{
	struct xlp9xx_i2c_dev *priv;
	struct resource *res;
	int err = 0;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->irq = platform_get_irq(pdev, 0);
	if (priv->irq <= 0) {
		dev_err(&pdev->dev, "invalid irq!\n");
		return priv->irq;
	}
	/* SMBAlert irq */
	priv->alert_data.irq = platform_get_irq(pdev, 1);
	if (priv->alert_data.irq <= 0)
		priv->alert_data.irq = 0;

	xlp9xx_i2c_get_frequency(pdev, priv);
	xlp9xx_i2c_init(priv);

	err = devm_request_irq(&pdev->dev, priv->irq, xlp9xx_i2c_isr, 0,
			       pdev->name, priv);
	if (err) {
		dev_err(&pdev->dev, "IRQ request failed!\n");
		return err;
	}

	init_completion(&priv->msg_complete);
	priv->adapter.dev.parent = &pdev->dev;
	priv->adapter.algo = &xlp9xx_i2c_algo;
	priv->adapter.class = I2C_CLASS_HWMON;
	ACPI_COMPANION_SET(&priv->adapter.dev, ACPI_COMPANION(&pdev->dev));
	priv->adapter.dev.of_node = pdev->dev.of_node;
	priv->dev = &pdev->dev;

	snprintf(priv->adapter.name, sizeof(priv->adapter.name), "xlp9xx-i2c");
	i2c_set_adapdata(&priv->adapter, priv);

	err = i2c_add_adapter(&priv->adapter);
	if (err)
		return err;

	err = xlp9xx_i2c_smbus_setup(priv, pdev);
	if (err)
		dev_dbg(&pdev->dev, "No active SMBus alert %d\n", err);

	platform_set_drvdata(pdev, priv);
	dev_dbg(&pdev->dev, "I2C bus:%d added\n", priv->adapter.nr);

	return 0;
}