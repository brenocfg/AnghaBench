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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int* bus_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVFN (int,int) ; 
 TYPE_1__* isst_cpu_info ; 
 int nr_cpu_ids ; 
 int num_possible_cpus () ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct pci_dev *isst_if_get_pci_dev(int cpu, int bus_no, int dev, int fn)
{
	int bus_number;

	if (bus_no < 0 || bus_no > 1 || cpu < 0 || cpu >= nr_cpu_ids ||
	    cpu >= num_possible_cpus())
		return NULL;

	bus_number = isst_cpu_info[cpu].bus_info[bus_no];
	if (bus_number < 0)
		return NULL;

	return pci_get_domain_bus_and_slot(0, bus_number, PCI_DEVFN(dev, fn));
}