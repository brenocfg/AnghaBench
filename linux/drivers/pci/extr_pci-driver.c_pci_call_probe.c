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
struct pci_driver {int dummy; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int is_probed; int /*<<< orphan*/  dev; } ;
struct drv_dev_and_id {struct pci_device_id const* member_2; struct pci_dev* member_1; struct pci_driver* member_0; } ;

/* Variables and functions */
 int MAX_NUMNODES ; 
 int /*<<< orphan*/  cpu_hotplug_disable () ; 
 int /*<<< orphan*/  cpu_hotplug_enable () ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int local_pci_probe (struct drv_dev_and_id*) ; 
 int /*<<< orphan*/  node_online (int) ; 
 int nr_cpu_ids ; 
 scalar_t__ pci_physfn_is_probed (struct pci_dev*) ; 
 int work_on_cpu (int,int (*) (struct drv_dev_and_id*),struct drv_dev_and_id*) ; 

__attribute__((used)) static int pci_call_probe(struct pci_driver *drv, struct pci_dev *dev,
			  const struct pci_device_id *id)
{
	int error, node, cpu;
	struct drv_dev_and_id ddi = { drv, dev, id };

	/*
	 * Execute driver initialization on node where the device is
	 * attached.  This way the driver likely allocates its local memory
	 * on the right node.
	 */
	node = dev_to_node(&dev->dev);
	dev->is_probed = 1;

	cpu_hotplug_disable();

	/*
	 * Prevent nesting work_on_cpu() for the case where a Virtual Function
	 * device is probed from work_on_cpu() of the Physical device.
	 */
	if (node < 0 || node >= MAX_NUMNODES || !node_online(node) ||
	    pci_physfn_is_probed(dev))
		cpu = nr_cpu_ids;
	else
		cpu = cpumask_any_and(cpumask_of_node(node), cpu_online_mask);

	if (cpu < nr_cpu_ids)
		error = work_on_cpu(cpu, local_pci_probe, &ddi);
	else
		error = local_pci_probe(&ddi);

	dev->is_probed = 0;
	cpu_hotplug_enable();
	return error;
}