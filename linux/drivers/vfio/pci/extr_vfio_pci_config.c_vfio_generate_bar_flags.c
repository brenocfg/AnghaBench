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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM_64 ; 
 unsigned long IORESOURCE_PREFETCH ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_MEM_PREFETCH ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_SPACE_IO ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_SPACE_MEMORY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_flags (struct pci_dev*,int) ; 

__attribute__((used)) static __le32 vfio_generate_bar_flags(struct pci_dev *pdev, int bar)
{
	unsigned long flags = pci_resource_flags(pdev, bar);
	u32 val;

	if (flags & IORESOURCE_IO)
		return cpu_to_le32(PCI_BASE_ADDRESS_SPACE_IO);

	val = PCI_BASE_ADDRESS_SPACE_MEMORY;

	if (flags & IORESOURCE_PREFETCH)
		val |= PCI_BASE_ADDRESS_MEM_PREFETCH;

	if (flags & IORESOURCE_MEM_64)
		val |= PCI_BASE_ADDRESS_MEM_TYPE_64;

	return cpu_to_le32(val);
}