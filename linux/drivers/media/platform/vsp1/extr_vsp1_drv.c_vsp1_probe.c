#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct vsp1_device {int version; TYPE_1__* info; TYPE_2__* dev; TYPE_2__* bus_master; int /*<<< orphan*/  fcp; int /*<<< orphan*/  mmio; int /*<<< orphan*/  videos; int /*<<< orphan*/  entities; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_15__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_14__ {int version; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VI6_IP_VERSION ; 
 int VI6_IP_VERSION_MODEL_MASK ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct vsp1_device* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vsp1_device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vsp1_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  rcar_fcp_get (struct device_node*) ; 
 TYPE_2__* rcar_fcp_get_device (int /*<<< orphan*/ ) ; 
 int vsp1_create_entities (struct vsp1_device*) ; 
 TYPE_1__* vsp1_device_infos ; 
 int /*<<< orphan*/  vsp1_irq_handler ; 
 int vsp1_read (struct vsp1_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsp1_probe(struct platform_device *pdev)
{
	struct vsp1_device *vsp1;
	struct device_node *fcp_node;
	struct resource *irq;
	struct resource *io;
	unsigned int i;
	int ret;

	vsp1 = devm_kzalloc(&pdev->dev, sizeof(*vsp1), GFP_KERNEL);
	if (vsp1 == NULL)
		return -ENOMEM;

	vsp1->dev = &pdev->dev;
	INIT_LIST_HEAD(&vsp1->entities);
	INIT_LIST_HEAD(&vsp1->videos);

	platform_set_drvdata(pdev, vsp1);

	/* I/O and IRQ resources (clock managed by the clock PM domain). */
	io = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	vsp1->mmio = devm_ioremap_resource(&pdev->dev, io);
	if (IS_ERR(vsp1->mmio))
		return PTR_ERR(vsp1->mmio);

	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq) {
		dev_err(&pdev->dev, "missing IRQ\n");
		return -EINVAL;
	}

	ret = devm_request_irq(&pdev->dev, irq->start, vsp1_irq_handler,
			      IRQF_SHARED, dev_name(&pdev->dev), vsp1);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		return ret;
	}

	/* FCP (optional). */
	fcp_node = of_parse_phandle(pdev->dev.of_node, "renesas,fcp", 0);
	if (fcp_node) {
		vsp1->fcp = rcar_fcp_get(fcp_node);
		of_node_put(fcp_node);
		if (IS_ERR(vsp1->fcp)) {
			dev_dbg(&pdev->dev, "FCP not found (%ld)\n",
				PTR_ERR(vsp1->fcp));
			return PTR_ERR(vsp1->fcp);
		}

		/*
		 * When the FCP is present, it handles all bus master accesses
		 * for the VSP and must thus be used in place of the VSP device
		 * to map DMA buffers.
		 */
		vsp1->bus_master = rcar_fcp_get_device(vsp1->fcp);
	} else {
		vsp1->bus_master = vsp1->dev;
	}

	/* Configure device parameters based on the version register. */
	pm_runtime_enable(&pdev->dev);

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0)
		goto done;

	vsp1->version = vsp1_read(vsp1, VI6_IP_VERSION);
	pm_runtime_put_sync(&pdev->dev);

	for (i = 0; i < ARRAY_SIZE(vsp1_device_infos); ++i) {
		if ((vsp1->version & VI6_IP_VERSION_MODEL_MASK) ==
		    vsp1_device_infos[i].version) {
			vsp1->info = &vsp1_device_infos[i];
			break;
		}
	}

	if (!vsp1->info) {
		dev_err(&pdev->dev, "unsupported IP version 0x%08x\n",
			vsp1->version);
		ret = -ENXIO;
		goto done;
	}

	dev_dbg(&pdev->dev, "IP version 0x%08x\n", vsp1->version);

	/* Instantiate entities. */
	ret = vsp1_create_entities(vsp1);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to create entities\n");
		goto done;
	}

done:
	if (ret)
		pm_runtime_disable(&pdev->dev);

	return ret;
}