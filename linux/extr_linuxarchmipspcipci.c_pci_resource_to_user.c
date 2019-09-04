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
struct resource {scalar_t__ start; } ;
struct pci_dev {int dummy; } ;
typedef  scalar_t__ resource_size_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ fixup_bigphys_addr (scalar_t__,scalar_t__) ; 
 scalar_t__ resource_size (struct resource const*) ; 

void pci_resource_to_user(const struct pci_dev *dev, int bar,
			  const struct resource *rsrc, resource_size_t *start,
			  resource_size_t *end)
{
	phys_addr_t size = resource_size(rsrc);

	*start = fixup_bigphys_addr(rsrc->start, size);
	*end = rsrc->start + size - 1;
}