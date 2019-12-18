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
struct qtnf_pcie_topaz_state {TYPE_1__ base; } ;
struct qtnf_bus {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct qtnf_bus* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct qtnf_pcie_topaz_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_pcie_topaz_probe ; 
 int /*<<< orphan*/  qtnf_pcie_topaz_remove ; 
 int /*<<< orphan*/  qtnf_pcie_topaz_resume ; 
 int /*<<< orphan*/  qtnf_pcie_topaz_suspend ; 
 int /*<<< orphan*/  qtnf_topaz_dma_mask_get ; 

struct qtnf_bus *qtnf_pcie_topaz_alloc(struct pci_dev *pdev)
{
	struct qtnf_bus *bus;
	struct qtnf_pcie_topaz_state *ts;

	bus = devm_kzalloc(&pdev->dev, sizeof(*bus) + sizeof(*ts), GFP_KERNEL);
	if (!bus)
		return NULL;

	ts = get_bus_priv(bus);
	ts->base.probe_cb = qtnf_pcie_topaz_probe;
	ts->base.remove_cb = qtnf_pcie_topaz_remove;
	ts->base.dma_mask_get_cb = qtnf_topaz_dma_mask_get;
#ifdef CONFIG_PM_SLEEP
	ts->base.resume_cb = qtnf_pcie_topaz_resume;
	ts->base.suspend_cb = qtnf_pcie_topaz_suspend;
#endif

	return bus;
}