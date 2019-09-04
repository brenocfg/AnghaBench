#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mvebu_gicp_spi_range {int dummy; } ;
struct mvebu_gicp {int spi_ranges_cnt; int /*<<< orphan*/  spi_cnt; void* spi_bitmap; TYPE_1__* spi_ranges; int /*<<< orphan*/  res; int /*<<< orphan*/  spi_lock; TYPE_2__* dev; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {scalar_t__ count; scalar_t__ start; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 void* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct mvebu_gicp* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gicp_domain_ops ; 
 int /*<<< orphan*/  gicp_msi_domain_info ; 
 struct irq_domain* irq_domain_create_hierarchy (struct irq_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mvebu_gicp*) ; 
 int /*<<< orphan*/  irq_domain_remove (struct irq_domain*) ; 
 struct irq_domain* irq_find_host (struct device_node*) ; 
 struct device_node* of_irq_find_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_to_fwnode (struct device_node*) ; 
 int of_property_count_u32_elems (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32_index (struct device_node*,char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_domain* platform_msi_create_irq_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct irq_domain*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mvebu_gicp*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mvebu_gicp_probe(struct platform_device *pdev)
{
	struct mvebu_gicp *gicp;
	struct irq_domain *inner_domain, *plat_domain, *parent_domain;
	struct device_node *node = pdev->dev.of_node;
	struct device_node *irq_parent_dn;
	int ret, i;

	gicp = devm_kzalloc(&pdev->dev, sizeof(*gicp), GFP_KERNEL);
	if (!gicp)
		return -ENOMEM;

	gicp->dev = &pdev->dev;
	spin_lock_init(&gicp->spi_lock);

	gicp->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!gicp->res)
		return -ENODEV;

	ret = of_property_count_u32_elems(node, "marvell,spi-ranges");
	if (ret < 0)
		return ret;

	gicp->spi_ranges_cnt = ret / 2;

	gicp->spi_ranges =
		devm_kcalloc(&pdev->dev,
			     gicp->spi_ranges_cnt,
			     sizeof(struct mvebu_gicp_spi_range),
			     GFP_KERNEL);
	if (!gicp->spi_ranges)
		return -ENOMEM;

	for (i = 0; i < gicp->spi_ranges_cnt; i++) {
		of_property_read_u32_index(node, "marvell,spi-ranges",
					   i * 2,
					   &gicp->spi_ranges[i].start);

		of_property_read_u32_index(node, "marvell,spi-ranges",
					   i * 2 + 1,
					   &gicp->spi_ranges[i].count);

		gicp->spi_cnt += gicp->spi_ranges[i].count;
	}

	gicp->spi_bitmap = devm_kcalloc(&pdev->dev,
				BITS_TO_LONGS(gicp->spi_cnt), sizeof(long),
				GFP_KERNEL);
	if (!gicp->spi_bitmap)
		return -ENOMEM;

	irq_parent_dn = of_irq_find_parent(node);
	if (!irq_parent_dn) {
		dev_err(&pdev->dev, "failed to find parent IRQ node\n");
		return -ENODEV;
	}

	parent_domain = irq_find_host(irq_parent_dn);
	if (!parent_domain) {
		dev_err(&pdev->dev, "failed to find parent IRQ domain\n");
		return -ENODEV;
	}

	inner_domain = irq_domain_create_hierarchy(parent_domain, 0,
						   gicp->spi_cnt,
						   of_node_to_fwnode(node),
						   &gicp_domain_ops, gicp);
	if (!inner_domain)
		return -ENOMEM;


	plat_domain = platform_msi_create_irq_domain(of_node_to_fwnode(node),
						     &gicp_msi_domain_info,
						     inner_domain);
	if (!plat_domain) {
		irq_domain_remove(inner_domain);
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, gicp);

	return 0;
}