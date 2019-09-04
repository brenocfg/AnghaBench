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
struct pci_device_id {int /*<<< orphan*/  device; scalar_t__ vendor; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  mask; scalar_t__ gen; int /*<<< orphan*/  used; } ;
struct TYPE_4__ {int num_possible_nodes; int /*<<< orphan*/  num_online_cpus; int /*<<< orphan*/  num_online_nodes; TYPE_1__ proc; int /*<<< orphan*/  num_core_siblings; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_weight (int /*<<< orphan*/ ) ; 
 struct pci_device_id* hfi1_pci_tbl ; 
 int* hfi1_per_node_cntr ; 
 int /*<<< orphan*/  init_real_cpu_mask () ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ node_affinity ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int /*<<< orphan*/  num_online_nodes () ; 
 int num_possible_nodes () ; 
 struct pci_dev* pci_get_device (scalar_t__,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int pcibus_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  topology_sibling_cpumask (int /*<<< orphan*/ ) ; 

int node_affinity_init(void)
{
	int node;
	struct pci_dev *dev = NULL;
	const struct pci_device_id *ids = hfi1_pci_tbl;

	cpumask_clear(&node_affinity.proc.used);
	cpumask_copy(&node_affinity.proc.mask, cpu_online_mask);

	node_affinity.proc.gen = 0;
	node_affinity.num_core_siblings =
				cpumask_weight(topology_sibling_cpumask(
					cpumask_first(&node_affinity.proc.mask)
					));
	node_affinity.num_possible_nodes = num_possible_nodes();
	node_affinity.num_online_nodes = num_online_nodes();
	node_affinity.num_online_cpus = num_online_cpus();

	/*
	 * The real cpu mask is part of the affinity struct but it has to be
	 * initialized early. It is needed to calculate the number of user
	 * contexts in set_up_context_variables().
	 */
	init_real_cpu_mask();

	hfi1_per_node_cntr = kcalloc(node_affinity.num_possible_nodes,
				     sizeof(*hfi1_per_node_cntr), GFP_KERNEL);
	if (!hfi1_per_node_cntr)
		return -ENOMEM;

	while (ids->vendor) {
		dev = NULL;
		while ((dev = pci_get_device(ids->vendor, ids->device, dev))) {
			node = pcibus_to_node(dev->bus);
			if (node < 0)
				goto out;

			hfi1_per_node_cntr[node]++;
		}
		ids++;
	}

	return 0;

out:
	/*
	 * Invalid PCI NUMA node information found, note it, and populate
	 * our database 1:1.
	 */
	pr_err("HFI: Invalid PCI NUMA node. Performance may be affected\n");
	pr_err("HFI: System BIOS may need to be upgraded\n");
	for (node = 0; node < node_affinity.num_possible_nodes; node++)
		hfi1_per_node_cntr[node] = 1;

	return 0;
}