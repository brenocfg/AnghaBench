#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct orion_mdio_dev {scalar_t__ regs; int err_interrupt; int /*<<< orphan*/ * clk; int /*<<< orphan*/  smi_busy_wait; } ;
struct mii_bus {char* name; struct orion_mdio_dev* priv; TYPE_1__* parent; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
typedef  enum orion_mdio_bus_type { ____Placeholder_orion_mdio_bus_type } orion_mdio_bus_type ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  BUS_TYPE_SMI 129 
#define  BUS_TYPE_XSMI 128 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 scalar_t__ MVMDIO_ERR_INT_MASK ; 
 int /*<<< orphan*/  MVMDIO_ERR_INT_SMI_DONE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 char* dev_name (TYPE_1__*) ; 
 scalar_t__ devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mii_bus* devm_mdiobus_alloc_size (TYPE_1__*,int) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct orion_mdio_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_clk_get (int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 int of_mdiobus_register (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orion_mdio_err_irq ; 
 int /*<<< orphan*/  orion_mdio_smi_read ; 
 int /*<<< orphan*/  orion_mdio_smi_write ; 
 int /*<<< orphan*/  orion_mdio_xsmi_read ; 
 int /*<<< orphan*/  orion_mdio_xsmi_write ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mii_bus*) ; 
 scalar_t__ resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int orion_mdio_probe(struct platform_device *pdev)
{
	enum orion_mdio_bus_type type;
	struct resource *r;
	struct mii_bus *bus;
	struct orion_mdio_dev *dev;
	int i, ret;

	type = (enum orion_mdio_bus_type)of_device_get_match_data(&pdev->dev);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		dev_err(&pdev->dev, "No SMI register address given\n");
		return -ENODEV;
	}

	bus = devm_mdiobus_alloc_size(&pdev->dev,
				      sizeof(struct orion_mdio_dev));
	if (!bus)
		return -ENOMEM;

	switch (type) {
	case BUS_TYPE_SMI:
		bus->read = orion_mdio_smi_read;
		bus->write = orion_mdio_smi_write;
		break;
	case BUS_TYPE_XSMI:
		bus->read = orion_mdio_xsmi_read;
		bus->write = orion_mdio_xsmi_write;
		break;
	}

	bus->name = "orion_mdio_bus";
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s-mii",
		 dev_name(&pdev->dev));
	bus->parent = &pdev->dev;

	dev = bus->priv;
	dev->regs = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	if (!dev->regs) {
		dev_err(&pdev->dev, "Unable to remap SMI register\n");
		return -ENODEV;
	}

	init_waitqueue_head(&dev->smi_busy_wait);

	for (i = 0; i < ARRAY_SIZE(dev->clk); i++) {
		dev->clk[i] = of_clk_get(pdev->dev.of_node, i);
		if (IS_ERR(dev->clk[i]))
			break;
		clk_prepare_enable(dev->clk[i]);
	}

	dev->err_interrupt = platform_get_irq(pdev, 0);
	if (dev->err_interrupt > 0 &&
	    resource_size(r) < MVMDIO_ERR_INT_MASK + 4) {
		dev_err(&pdev->dev,
			"disabling interrupt, resource size is too small\n");
		dev->err_interrupt = 0;
	}
	if (dev->err_interrupt > 0) {
		ret = devm_request_irq(&pdev->dev, dev->err_interrupt,
					orion_mdio_err_irq,
					IRQF_SHARED, pdev->name, dev);
		if (ret)
			goto out_mdio;

		writel(MVMDIO_ERR_INT_SMI_DONE,
			dev->regs + MVMDIO_ERR_INT_MASK);

	} else if (dev->err_interrupt == -EPROBE_DEFER) {
		ret = -EPROBE_DEFER;
		goto out_mdio;
	}

	ret = of_mdiobus_register(bus, pdev->dev.of_node);
	if (ret < 0) {
		dev_err(&pdev->dev, "Cannot register MDIO bus (%d)\n", ret);
		goto out_mdio;
	}

	platform_set_drvdata(pdev, bus);

	return 0;

out_mdio:
	if (dev->err_interrupt > 0)
		writel(0, dev->regs + MVMDIO_ERR_INT_MASK);

	for (i = 0; i < ARRAY_SIZE(dev->clk); i++) {
		if (IS_ERR(dev->clk[i]))
			break;
		clk_disable_unprepare(dev->clk[i]);
		clk_put(dev->clk[i]);
	}

	return ret;
}