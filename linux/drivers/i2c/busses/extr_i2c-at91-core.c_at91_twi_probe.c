#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_17__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct TYPE_16__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct TYPE_18__ {TYPE_1__ dev; int /*<<< orphan*/  timeout; int /*<<< orphan*/  nr; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct at91_twi_dev {scalar_t__ irq; TYPE_2__* dev; int /*<<< orphan*/  clk; TYPE_8__ adapter; scalar_t__ slave_detected; int /*<<< orphan*/  base; int /*<<< orphan*/  pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_I2C_TIMEOUT ; 
 int /*<<< orphan*/  AT91_TWI_VER ; 
 int /*<<< orphan*/  AUTOSUSPEND_TIMEOUT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  at91_init_twi_bus (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_get_driver_data (struct platform_device*) ; 
 int at91_twi_probe_master (struct platform_device*,int /*<<< orphan*/ ,struct at91_twi_dev*) ; 
 int at91_twi_probe_slave (struct platform_device*,int /*<<< orphan*/ ,struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_read (struct at91_twi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct at91_twi_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int i2c_add_numbered_adapter (TYPE_8__*) ; 
 scalar_t__ i2c_detect_slave_mode (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_8__*,struct at91_twi_dev*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct at91_twi_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int at91_twi_probe(struct platform_device *pdev)
{
	struct at91_twi_dev *dev;
	struct resource *mem;
	int rc;
	u32 phy_addr;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->dev = &pdev->dev;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!mem)
		return -ENODEV;
	phy_addr = mem->start;

	dev->pdata = at91_twi_get_driver_data(pdev);
	if (!dev->pdata)
		return -ENODEV;

	dev->base = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(dev->base))
		return PTR_ERR(dev->base);

	dev->irq = platform_get_irq(pdev, 0);
	if (dev->irq < 0)
		return dev->irq;

	platform_set_drvdata(pdev, dev);

	dev->clk = devm_clk_get(dev->dev, NULL);
	if (IS_ERR(dev->clk)) {
		dev_err(dev->dev, "no clock defined\n");
		return -ENODEV;
	}
	clk_prepare_enable(dev->clk);

	snprintf(dev->adapter.name, sizeof(dev->adapter.name), "AT91");
	i2c_set_adapdata(&dev->adapter, dev);
	dev->adapter.owner = THIS_MODULE;
	dev->adapter.class = I2C_CLASS_DEPRECATED;
	dev->adapter.dev.parent = dev->dev;
	dev->adapter.nr = pdev->id;
	dev->adapter.timeout = AT91_I2C_TIMEOUT;
	dev->adapter.dev.of_node = pdev->dev.of_node;

	dev->slave_detected = i2c_detect_slave_mode(&pdev->dev);

	if (dev->slave_detected)
		rc = at91_twi_probe_slave(pdev, phy_addr, dev);
	else
		rc = at91_twi_probe_master(pdev, phy_addr, dev);
	if (rc)
		return rc;

	at91_init_twi_bus(dev);

	pm_runtime_set_autosuspend_delay(dev->dev, AUTOSUSPEND_TIMEOUT);
	pm_runtime_use_autosuspend(dev->dev);
	pm_runtime_set_active(dev->dev);
	pm_runtime_enable(dev->dev);

	rc = i2c_add_numbered_adapter(&dev->adapter);
	if (rc) {
		clk_disable_unprepare(dev->clk);

		pm_runtime_disable(dev->dev);
		pm_runtime_set_suspended(dev->dev);

		return rc;
	}

	dev_info(dev->dev, "AT91 i2c bus driver (hw version: %#x).\n",
		 at91_twi_read(dev, AT91_TWI_VER));
	return 0;
}