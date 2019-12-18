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
typedef  int u16 ;
struct pci_dev {int revision; TYPE_1__* resource; } ;
struct drm_device {struct pci_dev* pdev; struct bochs_device* dev_private; } ;
struct bochs_device {int ioports; unsigned long fb_base; unsigned long fb_size; int qext_size; int /*<<< orphan*/ * mmio; int /*<<< orphan*/ * fb_map; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned long) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned long,...) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int IORESOURCE_MEM ; 
 int VBE_DISPI_ID0 ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_ID ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_VIDEO_MEMORY_64K ; 
 unsigned long VBE_DISPI_IOPORT_INDEX ; 
 int bochs_dispi_read (struct bochs_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bochs_hw_set_native_endian (struct bochs_device*) ; 
 void* ioremap (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 scalar_t__ pci_request_region (struct pci_dev*,int,char*) ; 
 unsigned long pci_resource_len (struct pci_dev*,int) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_region (unsigned long,unsigned long,char*) ; 

int bochs_hw_init(struct drm_device *dev)
{
	struct bochs_device *bochs = dev->dev_private;
	struct pci_dev *pdev = dev->pdev;
	unsigned long addr, size, mem, ioaddr, iosize;
	u16 id;

	if (pdev->resource[2].flags & IORESOURCE_MEM) {
		/* mmio bar with vga and bochs registers present */
		if (pci_request_region(pdev, 2, "bochs-drm") != 0) {
			DRM_ERROR("Cannot request mmio region\n");
			return -EBUSY;
		}
		ioaddr = pci_resource_start(pdev, 2);
		iosize = pci_resource_len(pdev, 2);
		bochs->mmio = ioremap(ioaddr, iosize);
		if (bochs->mmio == NULL) {
			DRM_ERROR("Cannot map mmio region\n");
			return -ENOMEM;
		}
	} else {
		ioaddr = VBE_DISPI_IOPORT_INDEX;
		iosize = 2;
		if (!request_region(ioaddr, iosize, "bochs-drm")) {
			DRM_ERROR("Cannot request ioports\n");
			return -EBUSY;
		}
		bochs->ioports = 1;
	}

	id = bochs_dispi_read(bochs, VBE_DISPI_INDEX_ID);
	mem = bochs_dispi_read(bochs, VBE_DISPI_INDEX_VIDEO_MEMORY_64K)
		* 64 * 1024;
	if ((id & 0xfff0) != VBE_DISPI_ID0) {
		DRM_ERROR("ID mismatch\n");
		return -ENODEV;
	}

	if ((pdev->resource[0].flags & IORESOURCE_MEM) == 0)
		return -ENODEV;
	addr = pci_resource_start(pdev, 0);
	size = pci_resource_len(pdev, 0);
	if (addr == 0)
		return -ENODEV;
	if (size != mem) {
		DRM_ERROR("Size mismatch: pci=%ld, bochs=%ld\n",
			size, mem);
		size = min(size, mem);
	}

	if (pci_request_region(pdev, 0, "bochs-drm") != 0) {
		DRM_ERROR("Cannot request framebuffer\n");
		return -EBUSY;
	}

	bochs->fb_map = ioremap(addr, size);
	if (bochs->fb_map == NULL) {
		DRM_ERROR("Cannot map framebuffer\n");
		return -ENOMEM;
	}
	bochs->fb_base = addr;
	bochs->fb_size = size;

	DRM_INFO("Found bochs VGA, ID 0x%x.\n", id);
	DRM_INFO("Framebuffer size %ld kB @ 0x%lx, %s @ 0x%lx.\n",
		 size / 1024, addr,
		 bochs->ioports ? "ioports" : "mmio",
		 ioaddr);

	if (bochs->mmio && pdev->revision >= 2) {
		bochs->qext_size = readl(bochs->mmio + 0x600);
		if (bochs->qext_size < 4 || bochs->qext_size > iosize) {
			bochs->qext_size = 0;
			goto noext;
		}
		DRM_DEBUG("Found qemu ext regs, size %ld\n",
			  bochs->qext_size);
		bochs_hw_set_native_endian(bochs);
	}

noext:
	return 0;
}