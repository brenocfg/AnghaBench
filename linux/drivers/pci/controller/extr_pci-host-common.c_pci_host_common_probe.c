#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {struct device* parent; } ;
struct pci_host_bridge {int /*<<< orphan*/  bus; int /*<<< orphan*/  swizzle_irq; int /*<<< orphan*/  map_irq; int /*<<< orphan*/ * ops; int /*<<< orphan*/  busnr; struct pci_config_window* sysdata; TYPE_1__ dev; int /*<<< orphan*/  windows; } ;
struct pci_ecam_ops {int /*<<< orphan*/  pci_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct pci_config_window {TYPE_2__ busr; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct pci_config_window*) ; 
 int /*<<< orphan*/  PCI_PROBE_ONLY ; 
 int /*<<< orphan*/  PCI_REASSIGN_ALL_BUS ; 
 int PTR_ERR (struct pci_config_window*) ; 
 struct pci_host_bridge* devm_pci_alloc_host_bridge (struct device*,int /*<<< orphan*/ ) ; 
 struct pci_config_window* gen_pci_init (struct device*,struct list_head*,struct pci_ecam_ops*) ; 
 int /*<<< orphan*/  list_splice_init (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_irq_parse_and_map_pci ; 
 int /*<<< orphan*/  of_pci_check_probe_only () ; 
 int /*<<< orphan*/  pci_add_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_common_swizzle ; 
 int /*<<< orphan*/  pci_free_resource_list (struct list_head*) ; 
 int /*<<< orphan*/  pci_has_flag (int /*<<< orphan*/ ) ; 
 int pci_host_probe (struct pci_host_bridge*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ ) ; 

int pci_host_common_probe(struct platform_device *pdev,
			  struct pci_ecam_ops *ops)
{
	struct device *dev = &pdev->dev;
	struct pci_host_bridge *bridge;
	struct pci_config_window *cfg;
	struct list_head resources;
	int ret;

	bridge = devm_pci_alloc_host_bridge(dev, 0);
	if (!bridge)
		return -ENOMEM;

	of_pci_check_probe_only();

	/* Parse and map our Configuration Space windows */
	cfg = gen_pci_init(dev, &resources, ops);
	if (IS_ERR(cfg))
		return PTR_ERR(cfg);

	/* Do not reassign resources if probe only */
	if (!pci_has_flag(PCI_PROBE_ONLY))
		pci_add_flags(PCI_REASSIGN_ALL_BUS);

	list_splice_init(&resources, &bridge->windows);
	bridge->dev.parent = dev;
	bridge->sysdata = cfg;
	bridge->busnr = cfg->busr.start;
	bridge->ops = &ops->pci_ops;
	bridge->map_irq = of_irq_parse_and_map_pci;
	bridge->swizzle_irq = pci_common_swizzle;

	ret = pci_host_probe(bridge);
	if (ret < 0) {
		pci_free_resource_list(&resources);
		return ret;
	}

	platform_set_drvdata(pdev, bridge->bus);
	return 0;
}