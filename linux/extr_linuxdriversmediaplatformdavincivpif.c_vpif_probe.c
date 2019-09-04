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
struct resource {int dummy; } ;
struct TYPE_7__ {struct TYPE_7__* parent; int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  of_node; } ;
struct platform_device {char* name; int id; int num_resources; TYPE_1__ dev; struct resource* resource; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct platform_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_next_endpoint (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  platform_device_register (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpif_base ; 
 int /*<<< orphan*/  vpif_lock ; 

__attribute__((used)) static int vpif_probe(struct platform_device *pdev)
{
	static struct resource	*res, *res_irq;
	struct platform_device *pdev_capture, *pdev_display;
	struct device_node *endpoint = NULL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	vpif_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(vpif_base))
		return PTR_ERR(vpif_base);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_get(&pdev->dev);

	spin_lock_init(&vpif_lock);
	dev_info(&pdev->dev, "vpif probe success\n");

	/*
	 * If VPIF Node has endpoints, assume "new" DT support,
	 * where capture and display drivers don't have DT nodes
	 * so their devices need to be registered manually here
	 * for their legacy platform_drivers to work.
	 */
	endpoint = of_graph_get_next_endpoint(pdev->dev.of_node,
					      endpoint);
	if (!endpoint)
		return 0;

	/*
	 * For DT platforms, manually create platform_devices for
	 * capture/display drivers.
	 */
	res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res_irq) {
		dev_warn(&pdev->dev, "Missing IRQ resource.\n");
		return -EINVAL;
	}

	pdev_capture = devm_kzalloc(&pdev->dev, sizeof(*pdev_capture),
				    GFP_KERNEL);
	if (pdev_capture) {
		pdev_capture->name = "vpif_capture";
		pdev_capture->id = -1;
		pdev_capture->resource = res_irq;
		pdev_capture->num_resources = 1;
		pdev_capture->dev.dma_mask = pdev->dev.dma_mask;
		pdev_capture->dev.coherent_dma_mask = pdev->dev.coherent_dma_mask;
		pdev_capture->dev.parent = &pdev->dev;
		platform_device_register(pdev_capture);
	} else {
		dev_warn(&pdev->dev, "Unable to allocate memory for pdev_capture.\n");
	}

	pdev_display = devm_kzalloc(&pdev->dev, sizeof(*pdev_display),
				    GFP_KERNEL);
	if (pdev_display) {
		pdev_display->name = "vpif_display";
		pdev_display->id = -1;
		pdev_display->resource = res_irq;
		pdev_display->num_resources = 1;
		pdev_display->dev.dma_mask = pdev->dev.dma_mask;
		pdev_display->dev.coherent_dma_mask = pdev->dev.coherent_dma_mask;
		pdev_display->dev.parent = &pdev->dev;
		platform_device_register(pdev_display);
	} else {
		dev_warn(&pdev->dev, "Unable to allocate memory for pdev_display.\n");
	}

	return 0;
}