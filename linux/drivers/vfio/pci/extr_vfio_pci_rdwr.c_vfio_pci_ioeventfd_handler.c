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
struct vfio_pci_ioeventfd {int count; int /*<<< orphan*/  addr; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfio_iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_iowrite64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfio_pci_ioeventfd_handler(void *opaque, void *unused)
{
	struct vfio_pci_ioeventfd *ioeventfd = opaque;

	switch (ioeventfd->count) {
	case 1:
		vfio_iowrite8(ioeventfd->data, ioeventfd->addr);
		break;
	case 2:
		vfio_iowrite16(ioeventfd->data, ioeventfd->addr);
		break;
	case 4:
		vfio_iowrite32(ioeventfd->data, ioeventfd->addr);
		break;
#ifdef iowrite64
	case 8:
		vfio_iowrite64(ioeventfd->data, ioeventfd->addr);
		break;
#endif
	}

	return 0;
}