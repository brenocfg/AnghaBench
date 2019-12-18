#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct mvebu_sei {void* sei_domain; void* ap_domain; void* cp_domain; TYPE_3__* caps; TYPE_4__* dev; int /*<<< orphan*/  base; int /*<<< orphan*/  res; int /*<<< orphan*/  mask_lock; int /*<<< orphan*/  cp_msi_lock; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_9__ {scalar_t__ size; } ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_10__ {TYPE_2__ cp_range; TYPE_1__ ap_range; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_GENERIC_MSI ; 
 int /*<<< orphan*/  DOMAIN_BUS_NEXUS ; 
 int /*<<< orphan*/  DOMAIN_BUS_WIRED ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct mvebu_sei* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 void* irq_domain_create_hierarchy (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mvebu_sei*) ; 
 void* irq_domain_create_linear (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct mvebu_sei*) ; 
 int /*<<< orphan*/  irq_domain_remove (void*) ; 
 int /*<<< orphan*/  irq_domain_update_bus_token (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (scalar_t__,int /*<<< orphan*/ ,struct mvebu_sei*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvebu_sei_ap_domain_ops ; 
 int /*<<< orphan*/  mvebu_sei_cp_domain_ops ; 
 int /*<<< orphan*/  mvebu_sei_domain_ops ; 
 int /*<<< orphan*/  mvebu_sei_handle_cascade_irq ; 
 int /*<<< orphan*/  mvebu_sei_msi_domain_info ; 
 int /*<<< orphan*/  mvebu_sei_reset (struct mvebu_sei*) ; 
 TYPE_3__* of_device_get_match_data (TYPE_4__*) ; 
 int /*<<< orphan*/  of_node_to_fwnode (struct device_node*) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_domain* platform_msi_create_irq_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mvebu_sei_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct irq_domain *plat_domain;
	struct mvebu_sei *sei;
	u32 parent_irq;
	int ret;

	sei = devm_kzalloc(&pdev->dev, sizeof(*sei), GFP_KERNEL);
	if (!sei)
		return -ENOMEM;

	sei->dev = &pdev->dev;

	mutex_init(&sei->cp_msi_lock);
	raw_spin_lock_init(&sei->mask_lock);

	sei->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sei->base = devm_ioremap_resource(sei->dev, sei->res);
	if (IS_ERR(sei->base)) {
		dev_err(sei->dev, "Failed to remap SEI resource\n");
		return PTR_ERR(sei->base);
	}

	/* Retrieve the SEI capabilities with the interrupt ranges */
	sei->caps = of_device_get_match_data(&pdev->dev);
	if (!sei->caps) {
		dev_err(sei->dev,
			"Could not retrieve controller capabilities\n");
		return -EINVAL;
	}

	/*
	 * Reserve the single (top-level) parent SPI IRQ from which all the
	 * interrupts handled by this driver will be signaled.
	 */
	parent_irq = irq_of_parse_and_map(node, 0);
	if (parent_irq <= 0) {
		dev_err(sei->dev, "Failed to retrieve top-level SPI IRQ\n");
		return -ENODEV;
	}

	/* Create the root SEI domain */
	sei->sei_domain = irq_domain_create_linear(of_node_to_fwnode(node),
						   (sei->caps->ap_range.size +
						    sei->caps->cp_range.size),
						   &mvebu_sei_domain_ops,
						   sei);
	if (!sei->sei_domain) {
		dev_err(sei->dev, "Failed to create SEI IRQ domain\n");
		ret = -ENOMEM;
		goto dispose_irq;
	}

	irq_domain_update_bus_token(sei->sei_domain, DOMAIN_BUS_NEXUS);

	/* Create the 'wired' domain */
	sei->ap_domain = irq_domain_create_hierarchy(sei->sei_domain, 0,
						     sei->caps->ap_range.size,
						     of_node_to_fwnode(node),
						     &mvebu_sei_ap_domain_ops,
						     sei);
	if (!sei->ap_domain) {
		dev_err(sei->dev, "Failed to create AP IRQ domain\n");
		ret = -ENOMEM;
		goto remove_sei_domain;
	}

	irq_domain_update_bus_token(sei->ap_domain, DOMAIN_BUS_WIRED);

	/* Create the 'MSI' domain */
	sei->cp_domain = irq_domain_create_hierarchy(sei->sei_domain, 0,
						     sei->caps->cp_range.size,
						     of_node_to_fwnode(node),
						     &mvebu_sei_cp_domain_ops,
						     sei);
	if (!sei->cp_domain) {
		pr_err("Failed to create CPs IRQ domain\n");
		ret = -ENOMEM;
		goto remove_ap_domain;
	}

	irq_domain_update_bus_token(sei->cp_domain, DOMAIN_BUS_GENERIC_MSI);

	plat_domain = platform_msi_create_irq_domain(of_node_to_fwnode(node),
						     &mvebu_sei_msi_domain_info,
						     sei->cp_domain);
	if (!plat_domain) {
		pr_err("Failed to create CPs MSI domain\n");
		ret = -ENOMEM;
		goto remove_cp_domain;
	}

	mvebu_sei_reset(sei);

	irq_set_chained_handler_and_data(parent_irq,
					 mvebu_sei_handle_cascade_irq,
					 sei);

	return 0;

remove_cp_domain:
	irq_domain_remove(sei->cp_domain);
remove_ap_domain:
	irq_domain_remove(sei->ap_domain);
remove_sei_domain:
	irq_domain_remove(sei->sei_domain);
dispose_irq:
	irq_dispose_mapping(parent_irq);

	return ret;
}