#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int flags; scalar_t__ end; scalar_t__ start; } ;
struct vfio_pci_dummy_resource {int index; int /*<<< orphan*/  res_next; TYPE_2__ resource; } ;
struct vfio_pci_device {int* bar_mmap_supported; int /*<<< orphan*/  dummy_resources_list; TYPE_1__* pdev; } ;
struct resource {int flags; int start; int /*<<< orphan*/  parent; scalar_t__ end; } ;
struct TYPE_3__ {struct resource* resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_VFIO_PCI_MMAP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int PCI_STD_RESOURCES ; 
 int PCI_STD_RESOURCE_END ; 
 int /*<<< orphan*/  kfree (struct vfio_pci_dummy_resource*) ; 
 struct vfio_pci_dummy_resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ request_resource (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ resource_size (struct resource*) ; 

__attribute__((used)) static void vfio_pci_probe_mmaps(struct vfio_pci_device *vdev)
{
	struct resource *res;
	int bar;
	struct vfio_pci_dummy_resource *dummy_res;

	INIT_LIST_HEAD(&vdev->dummy_resources_list);

	for (bar = PCI_STD_RESOURCES; bar <= PCI_STD_RESOURCE_END; bar++) {
		res = vdev->pdev->resource + bar;

		if (!IS_ENABLED(CONFIG_VFIO_PCI_MMAP))
			goto no_mmap;

		if (!(res->flags & IORESOURCE_MEM))
			goto no_mmap;

		/*
		 * The PCI core shouldn't set up a resource with a
		 * type but zero size. But there may be bugs that
		 * cause us to do that.
		 */
		if (!resource_size(res))
			goto no_mmap;

		if (resource_size(res) >= PAGE_SIZE) {
			vdev->bar_mmap_supported[bar] = true;
			continue;
		}

		if (!(res->start & ~PAGE_MASK)) {
			/*
			 * Add a dummy resource to reserve the remainder
			 * of the exclusive page in case that hot-add
			 * device's bar is assigned into it.
			 */
			dummy_res = kzalloc(sizeof(*dummy_res), GFP_KERNEL);
			if (dummy_res == NULL)
				goto no_mmap;

			dummy_res->resource.name = "vfio sub-page reserved";
			dummy_res->resource.start = res->end + 1;
			dummy_res->resource.end = res->start + PAGE_SIZE - 1;
			dummy_res->resource.flags = res->flags;
			if (request_resource(res->parent,
						&dummy_res->resource)) {
				kfree(dummy_res);
				goto no_mmap;
			}
			dummy_res->index = bar;
			list_add(&dummy_res->res_next,
					&vdev->dummy_resources_list);
			vdev->bar_mmap_supported[bar] = true;
			continue;
		}
		/*
		 * Here we don't handle the case when the BAR is not page
		 * aligned because we can't expect the BAR will be
		 * assigned into the same location in a page in guest
		 * when we passthrough the BAR. And it's hard to access
		 * this BAR in userspace because we have no way to get
		 * the BAR's location in a page.
		 */
no_mmap:
		vdev->bar_mmap_supported[bar] = false;
	}
}