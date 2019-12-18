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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpumap_print_to_pagebuf (int,char*,struct cpumask const*) ; 
 struct cpumask* cpumask_of_pcibus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_bus (struct device*) ; 

__attribute__((used)) static ssize_t cpulistaffinity_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	const struct cpumask *cpumask = cpumask_of_pcibus(to_pci_bus(dev));

	return cpumap_print_to_pagebuf(true, buf, cpumask);
}