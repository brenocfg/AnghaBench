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
struct irq_alloc_info {int ioapic_node; scalar_t__ ioapic_valid; } ;

/* Variables and functions */
 int NUMA_NO_NODE ; 

__attribute__((used)) static int ioapic_alloc_attr_node(struct irq_alloc_info *info)
{
	return (info && info->ioapic_valid) ? info->ioapic_node : NUMA_NO_NODE;
}