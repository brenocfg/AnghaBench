#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  suspend_cb; int /*<<< orphan*/  resume_cb; int /*<<< orphan*/  dma_mask_get_cb; int /*<<< orphan*/  remove_cb; int /*<<< orphan*/  probe_cb; } ;
struct qtnf_pcie_pearl_state {TYPE_1__ base; } ;
struct qtnf_bus {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct qtnf_bus* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct qtnf_pcie_pearl_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_pcie_pearl_probe ; 
 int /*<<< orphan*/  qtnf_pcie_pearl_remove ; 
 int /*<<< orphan*/  qtnf_pcie_pearl_resume ; 
 int /*<<< orphan*/  qtnf_pcie_pearl_suspend ; 
 int /*<<< orphan*/  qtnf_pearl_dma_mask_get ; 

struct qtnf_bus *qtnf_pcie_pearl_alloc(struct pci_dev *pdev)
{
	struct qtnf_bus *bus;
	struct qtnf_pcie_pearl_state *ps;

	bus = devm_kzalloc(&pdev->dev, sizeof(*bus) + sizeof(*ps), GFP_KERNEL);
	if (!bus)
		return NULL;

	ps = get_bus_priv(bus);
	ps->base.probe_cb = qtnf_pcie_pearl_probe;
	ps->base.remove_cb = qtnf_pcie_pearl_remove;
	ps->base.dma_mask_get_cb = qtnf_pearl_dma_mask_get;
#ifdef CONFIG_PM_SLEEP
	ps->base.resume_cb = qtnf_pcie_pearl_resume;
	ps->base.suspend_cb = qtnf_pcie_pearl_suspend;
#endif

	return bus;
}