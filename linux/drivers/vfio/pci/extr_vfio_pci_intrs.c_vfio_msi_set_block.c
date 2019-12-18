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
struct vfio_pci_device {unsigned int num_ctx; } ;
typedef  int int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int vfio_msi_set_vector_signal (struct vfio_pci_device*,int,int,int) ; 

__attribute__((used)) static int vfio_msi_set_block(struct vfio_pci_device *vdev, unsigned start,
			      unsigned count, int32_t *fds, bool msix)
{
	int i, j, ret = 0;

	if (start >= vdev->num_ctx || start + count > vdev->num_ctx)
		return -EINVAL;

	for (i = 0, j = start; i < count && !ret; i++, j++) {
		int fd = fds ? fds[i] : -1;
		ret = vfio_msi_set_vector_signal(vdev, j, fd, msix);
	}

	if (ret) {
		for (--j; j >= (int)start; j--)
			vfio_msi_set_vector_signal(vdev, j, -1, msix);
	}

	return ret;
}