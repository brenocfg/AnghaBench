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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 struct cpumask* cpu_online_mask ; 
 int /*<<< orphan*/  cpumap_print_to_pagebuf (int,char*,struct cpumask const*) ; 
 struct cpumask* cpumask_of_node (int) ; 
 struct cpumask* cpumask_of_pcibus (int /*<<< orphan*/ ) ; 
 int dev_to_node (struct device*) ; 
 TYPE_1__* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t pci_dev_show_local_cpu(struct device *dev, bool list,
				      struct device_attribute *attr, char *buf)
{
	const struct cpumask *mask;

#ifdef CONFIG_NUMA
	mask = (dev_to_node(dev) == -1) ? cpu_online_mask :
					  cpumask_of_node(dev_to_node(dev));
#else
	mask = cpumask_of_pcibus(to_pci_dev(dev)->bus);
#endif
	return cpumap_print_to_pagebuf(list, buf, mask);
}