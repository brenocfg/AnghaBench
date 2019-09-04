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
struct resource {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct pci_host_bridge {int busnr; TYPE_3__* bus; int /*<<< orphan*/  map_irq; int /*<<< orphan*/  swizzle_irq; int /*<<< orphan*/  ops; struct pci_channel* sysdata; TYPE_1__ dev; int /*<<< orphan*/  windows; } ;
struct pci_channel {int nr_resources; int need_domain_info; TYPE_3__* bus; scalar_t__ index; int /*<<< orphan*/  pci_ops; scalar_t__ mem_offset; scalar_t__ io_offset; struct resource* resources; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_7__ {int end; } ;
struct TYPE_8__ {TYPE_2__ busn_res; } ;

/* Variables and functions */
 int IORESOURCE_DISABLED ; 
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_add_resource_offset (int /*<<< orphan*/ *,struct resource*,scalar_t__) ; 
 struct pci_host_bridge* pci_alloc_host_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bus_add_devices (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_bus_assign_resources (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_bus_size_bridges (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_common_swizzle ; 
 int /*<<< orphan*/  pci_free_host_bridge (struct pci_host_bridge*) ; 
 int pci_scan_root_bus_bridge (struct pci_host_bridge*) ; 
 int /*<<< orphan*/  pcibios_map_platform_irq ; 
 int /*<<< orphan*/  resources ; 

__attribute__((used)) static void pcibios_scanbus(struct pci_channel *hose)
{
	static int next_busno;
	static int need_domain_info;
	LIST_HEAD(resources);
	struct resource *res;
	resource_size_t offset;
	int i, ret;
	struct pci_host_bridge *bridge;

	bridge = pci_alloc_host_bridge(0);
	if (!bridge)
		return;

	for (i = 0; i < hose->nr_resources; i++) {
		res = hose->resources + i;
		offset = 0;
		if (res->flags & IORESOURCE_DISABLED)
			continue;
		if (res->flags & IORESOURCE_IO)
			offset = hose->io_offset;
		else if (res->flags & IORESOURCE_MEM)
			offset = hose->mem_offset;
		pci_add_resource_offset(&resources, res, offset);
	}

	list_splice_init(&resources, &bridge->windows);
	bridge->dev.parent = NULL;
	bridge->sysdata = hose;
	bridge->busnr = next_busno;
	bridge->ops = hose->pci_ops;
	bridge->swizzle_irq = pci_common_swizzle;
	bridge->map_irq = pcibios_map_platform_irq;

	ret = pci_scan_root_bus_bridge(bridge);
	if (ret) {
		pci_free_host_bridge(bridge);
		return;
	}

	hose->bus = bridge->bus;

	need_domain_info = need_domain_info || hose->index;
	hose->need_domain_info = need_domain_info;

	next_busno = hose->bus->busn_res.end + 1;
	/* Don't allow 8-bit bus number overflow inside the hose -
	   reserve some space for bridges. */
	if (next_busno > 224) {
		next_busno = 0;
		need_domain_info = 1;
	}

	pci_bus_size_bridges(hose->bus);
	pci_bus_assign_resources(hose->bus);
	pci_bus_add_devices(hose->bus);
}