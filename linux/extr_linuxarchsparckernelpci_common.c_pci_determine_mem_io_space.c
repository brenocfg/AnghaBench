#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_8__ {unsigned long start; unsigned long end; void* flags; int /*<<< orphan*/  name; } ;
struct pci_pbm_info {unsigned long config_space; unsigned long io_offset; unsigned long mem_offset; unsigned long mem64_offset; TYPE_3__ mem64_space; TYPE_3__ mem_space; TYPE_3__ io_space; int /*<<< orphan*/  name; TYPE_2__* op; } ;
struct linux_prom_pci_ranges {int parent_phys_hi; int parent_phys_lo; int child_phys_mid; int child_phys_lo; int size_hi; int size_lo; int child_phys_hi; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 void* IORESOURCE_IO ; 
 void* IORESOURCE_MEM ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  ioport_resource ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct linux_prom_pci_ranges* of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  pci_register_iommu_region (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  prom_halt () ; 
 int /*<<< orphan*/  prom_printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  request_resource (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ tlb_type ; 

void pci_determine_mem_io_space(struct pci_pbm_info *pbm)
{
	const struct linux_prom_pci_ranges *pbm_ranges;
	int i, saw_mem, saw_io;
	int num_pbm_ranges;

	/* Corresponding generic code in of_pci_get_host_bridge_resources() */

	saw_mem = saw_io = 0;
	pbm_ranges = of_get_property(pbm->op->dev.of_node, "ranges", &i);
	if (!pbm_ranges) {
		prom_printf("PCI: Fatal error, missing PBM ranges property "
			    " for %s\n",
			    pbm->name);
		prom_halt();
	}

	num_pbm_ranges = i / sizeof(*pbm_ranges);
	memset(&pbm->mem64_space, 0, sizeof(struct resource));

	for (i = 0; i < num_pbm_ranges; i++) {
		const struct linux_prom_pci_ranges *pr = &pbm_ranges[i];
		unsigned long a, size, region_a;
		u32 parent_phys_hi, parent_phys_lo;
		u32 child_phys_mid, child_phys_lo;
		u32 size_hi, size_lo;
		int type;

		parent_phys_hi = pr->parent_phys_hi;
		parent_phys_lo = pr->parent_phys_lo;
		child_phys_mid = pr->child_phys_mid;
		child_phys_lo = pr->child_phys_lo;
		if (tlb_type == hypervisor)
			parent_phys_hi &= 0x0fffffff;

		size_hi = pr->size_hi;
		size_lo = pr->size_lo;

		type = (pr->child_phys_hi >> 24) & 0x3;
		a = (((unsigned long)parent_phys_hi << 32UL) |
		     ((unsigned long)parent_phys_lo  <<  0UL));
		region_a = (((unsigned long)child_phys_mid << 32UL) |
		     ((unsigned long)child_phys_lo  <<  0UL));
		size = (((unsigned long)size_hi << 32UL) |
			((unsigned long)size_lo  <<  0UL));

		switch (type) {
		case 0:
			/* PCI config space, 16MB */
			pbm->config_space = a;
			break;

		case 1:
			/* 16-bit IO space, 16MB */
			pbm->io_space.start = a;
			pbm->io_space.end = a + size - 1UL;
			pbm->io_space.flags = IORESOURCE_IO;
			pbm->io_offset = a - region_a;
			saw_io = 1;
			break;

		case 2:
			/* 32-bit MEM space, 2GB */
			pbm->mem_space.start = a;
			pbm->mem_space.end = a + size - 1UL;
			pbm->mem_space.flags = IORESOURCE_MEM;
			pbm->mem_offset = a - region_a;
			saw_mem = 1;
			break;

		case 3:
			/* 64-bit MEM handling */
			pbm->mem64_space.start = a;
			pbm->mem64_space.end = a + size - 1UL;
			pbm->mem64_space.flags = IORESOURCE_MEM;
			pbm->mem64_offset = a - region_a;
			saw_mem = 1;
			break;

		default:
			break;
		}
	}

	if (!saw_io || !saw_mem) {
		prom_printf("%s: Fatal error, missing %s PBM range.\n",
			    pbm->name,
			    (!saw_io ? "IO" : "MEM"));
		prom_halt();
	}

	if (pbm->io_space.flags)
		printk("%s: PCI IO %pR offset %llx\n",
		       pbm->name, &pbm->io_space, pbm->io_offset);
	if (pbm->mem_space.flags)
		printk("%s: PCI MEM %pR offset %llx\n",
		       pbm->name, &pbm->mem_space, pbm->mem_offset);
	if (pbm->mem64_space.flags && pbm->mem_space.flags) {
		if (pbm->mem64_space.start <= pbm->mem_space.end)
			pbm->mem64_space.start = pbm->mem_space.end + 1;
		if (pbm->mem64_space.start > pbm->mem64_space.end)
			pbm->mem64_space.flags = 0;
	}

	if (pbm->mem64_space.flags)
		printk("%s: PCI MEM64 %pR offset %llx\n",
		       pbm->name, &pbm->mem64_space, pbm->mem64_offset);

	pbm->io_space.name = pbm->mem_space.name = pbm->name;
	pbm->mem64_space.name = pbm->name;

	request_resource(&ioport_resource, &pbm->io_space);
	request_resource(&iomem_resource, &pbm->mem_space);
	if (pbm->mem64_space.flags)
		request_resource(&iomem_resource, &pbm->mem64_space);

	pci_register_iommu_region(pbm);
}