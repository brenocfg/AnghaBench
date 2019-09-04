#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_18__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct TYPE_17__ {scalar_t__ of_node; TYPE_2__* parent; } ;
struct TYPE_19__ {TYPE_1__ dev; int /*<<< orphan*/  timeout; int /*<<< orphan*/  nr; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * algo; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct at91_twi_dev {scalar_t__ irq; TYPE_2__* dev; int /*<<< orphan*/  clk; TYPE_8__ adapter; int /*<<< orphan*/  fifo_size; int /*<<< orphan*/  base; int /*<<< orphan*/  pdata; int /*<<< orphan*/  cmd_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_I2C_TIMEOUT ; 
 int /*<<< orphan*/  AT91_TWI_VER ; 
 int /*<<< orphan*/  AUTOSUSPEND_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_TWI_CLK_HZ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  at91_calc_twi_clock (struct at91_twi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_init_twi_bus (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_algorithm ; 
 int at91_twi_configure_dma (struct at91_twi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_twi_get_driver_data (struct platform_device*) ; 
 int /*<<< orphan*/  at91_twi_quirks ; 
 int /*<<< orphan*/  at91_twi_read (struct at91_twi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_twi_interrupt ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct at91_twi_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct at91_twi_dev*) ; 
 int i2c_add_numbered_adapter (TYPE_8__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_8__*,struct at91_twi_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (scalar_t__,char*,int /*<<< orphan*/ *) ; 
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
	u32 bus_clk_rate;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;
	init_completion(&dev->cmd_complete);
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

	rc = devm_request_irq(&pdev->dev, dev->irq, atmel_twi_interrupt, 0,
			 dev_name(dev->dev), dev);
	if (rc) {
		dev_err(dev->dev, "Cannot get irq %d: %d\n", dev->irq, rc);
		return rc;
	}

	platform_set_drvdata(pdev, dev);

	dev->clk = devm_clk_get(dev->dev, NULL);
	if (IS_ERR(dev->clk)) {
		dev_err(dev->dev, "no clock defined\n");
		return -ENODEV;
	}
	rc = clk_prepare_enable(dev->clk);
	if (rc)
		return rc;

	if (dev->dev->of_node) {
		rc = at91_twi_configure_dma(dev, phy_addr);
		if (rc == -EPROBE_DEFER) {
			clk_disable_unprepare(dev->clk);
			return rc;
		}
	}

	if (!of_property_read_u32(pdev->dev.of_node, "atmel,fifo-size",
				  &dev->fifo_size)) {
		dev_info(dev->dev, "Using FIFO (%u data)\n", dev->fifo_size);
	}

	rc = of_property_read_u32(dev->dev->of_node, "clock-frequency",
			&bus_clk_rate);
	if (rc)
		bus_clk_rate = DEFAULT_TWI_CLK_HZ;

	at91_calc_twi_clock(dev, bus_clk_rate);
	at91_init_twi_bus(dev);

	snprintf(dev->adapter.name, sizeof(dev->adapter.name), "AT91");
	i2c_set_adapdata(&dev->adapter, dev);
	dev->adapter.owner = THIS_MODULE;
	dev->adapter.class = I2C_CLASS_DEPRECATED;
	dev->adapter.algo = &at91_twi_algorithm;
	dev->adapter.quirks = &at91_twi_quirks;
	dev->adapter.dev.parent = dev->dev;
	dev->adapter.nr = pdev->id;
	dev->adapter.timeout = AT91_I2C_TIMEOUT;
	dev->adapter.dev.of_node = pdev->dev.of_node;

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