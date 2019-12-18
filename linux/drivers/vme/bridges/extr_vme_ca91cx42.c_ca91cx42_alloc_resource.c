#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long end; scalar_t__ name; scalar_t__ start; int /*<<< orphan*/  flags; } ;
struct vme_master_resource {int number; TYPE_1__ bus_resource; int /*<<< orphan*/ * kern_base; struct vme_bridge* parent; } ;
struct vme_bridge {char* name; int /*<<< orphan*/  parent; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  PCIBIOS_MIN_MEM ; 
 scalar_t__ VMENAMSIZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ioremap_nocache (scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int pci_bus_alloc_resource (int /*<<< orphan*/ ,TYPE_1__*,unsigned long long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca91cx42_alloc_resource(struct vme_master_resource *image,
	unsigned long long size)
{
	unsigned long long existing_size;
	int retval = 0;
	struct pci_dev *pdev;
	struct vme_bridge *ca91cx42_bridge;

	ca91cx42_bridge = image->parent;

	/* Find pci_dev container of dev */
	if (!ca91cx42_bridge->parent) {
		dev_err(ca91cx42_bridge->parent, "Dev entry NULL\n");
		return -EINVAL;
	}
	pdev = to_pci_dev(ca91cx42_bridge->parent);

	existing_size = (unsigned long long)(image->bus_resource.end -
		image->bus_resource.start);

	/* If the existing size is OK, return */
	if (existing_size == (size - 1))
		return 0;

	if (existing_size != 0) {
		iounmap(image->kern_base);
		image->kern_base = NULL;
		kfree(image->bus_resource.name);
		release_resource(&image->bus_resource);
		memset(&image->bus_resource, 0, sizeof(image->bus_resource));
	}

	if (!image->bus_resource.name) {
		image->bus_resource.name = kmalloc(VMENAMSIZ+3, GFP_ATOMIC);
		if (!image->bus_resource.name) {
			retval = -ENOMEM;
			goto err_name;
		}
	}

	sprintf((char *)image->bus_resource.name, "%s.%d",
		ca91cx42_bridge->name, image->number);

	image->bus_resource.start = 0;
	image->bus_resource.end = (unsigned long)size;
	image->bus_resource.flags = IORESOURCE_MEM;

	retval = pci_bus_alloc_resource(pdev->bus,
		&image->bus_resource, size, 0x10000, PCIBIOS_MIN_MEM,
		0, NULL, NULL);
	if (retval) {
		dev_err(ca91cx42_bridge->parent, "Failed to allocate mem "
			"resource for window %d size 0x%lx start 0x%lx\n",
			image->number, (unsigned long)size,
			(unsigned long)image->bus_resource.start);
		goto err_resource;
	}

	image->kern_base = ioremap_nocache(
		image->bus_resource.start, size);
	if (!image->kern_base) {
		dev_err(ca91cx42_bridge->parent, "Failed to remap resource\n");
		retval = -ENOMEM;
		goto err_remap;
	}

	return 0;

err_remap:
	release_resource(&image->bus_resource);
err_resource:
	kfree(image->bus_resource.name);
	memset(&image->bus_resource, 0, sizeof(image->bus_resource));
err_name:
	return retval;
}