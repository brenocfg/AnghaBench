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
struct uio_mem {char const* name; int addr; int offs; int size; int /*<<< orphan*/  internal_addr; int /*<<< orphan*/  memtype; } ;
struct pci_dev {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int ENODEV ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  UIO_MEM_PHYS ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int) ; 
 int pci_resource_len (struct pci_dev*,int) ; 
 int pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static int mf624_setup_mem(struct pci_dev *dev, int bar, struct uio_mem *mem, const char *name)
{
	resource_size_t start = pci_resource_start(dev, bar);
	resource_size_t len = pci_resource_len(dev, bar);

	mem->name = name;
	mem->addr = start & PAGE_MASK;
	mem->offs = start & ~PAGE_MASK;
	if (!mem->addr)
		return -ENODEV;
	mem->size = ((start & ~PAGE_MASK) + len + PAGE_SIZE - 1) & PAGE_MASK;
	mem->memtype = UIO_MEM_PHYS;
	mem->internal_addr = pci_ioremap_bar(dev, bar);
	if (!mem->internal_addr)
		return -ENODEV;
	return 0;
}