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
struct xilly_endpoint_hardware {int dummy; } ;
struct xilly_endpoint {int /*<<< orphan*/  dev; int /*<<< orphan*/  registers; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct xilly_endpoint*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xilly_endpoint*) ; 
 struct xilly_endpoint_hardware of_hw ; 
 struct xilly_endpoint_hardware of_hw_coherent ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xillybus_endpoint_discovery (struct xilly_endpoint*) ; 
 struct xilly_endpoint* xillybus_init_endpoint (int /*<<< orphan*/ *,struct device*,struct xilly_endpoint_hardware*) ; 
 int /*<<< orphan*/  xillybus_isr ; 
 int /*<<< orphan*/  xillyname ; 

__attribute__((used)) static int xilly_drv_probe(struct platform_device *op)
{
	struct device *dev = &op->dev;
	struct xilly_endpoint *endpoint;
	int rc;
	int irq;
	struct resource *res;
	struct xilly_endpoint_hardware *ephw = &of_hw;

	if (of_property_read_bool(dev->of_node, "dma-coherent"))
		ephw = &of_hw_coherent;

	endpoint = xillybus_init_endpoint(NULL, dev, ephw);

	if (!endpoint)
		return -ENOMEM;

	dev_set_drvdata(dev, endpoint);

	res = platform_get_resource(op, IORESOURCE_MEM, 0);
	endpoint->registers = devm_ioremap_resource(dev, res);

	if (IS_ERR(endpoint->registers))
		return PTR_ERR(endpoint->registers);

	irq = platform_get_irq(op, 0);

	rc = devm_request_irq(dev, irq, xillybus_isr, 0, xillyname, endpoint);

	if (rc) {
		dev_err(endpoint->dev,
			"Failed to register IRQ handler. Aborting.\n");
		return -ENODEV;
	}

	return xillybus_endpoint_discovery(endpoint);
}