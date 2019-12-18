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
struct virtio_iommu_req_tail {int status; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int ERANGE ; 
#define  VIRTIO_IOMMU_S_DEVERR 136 
#define  VIRTIO_IOMMU_S_FAULT 135 
#define  VIRTIO_IOMMU_S_INVAL 134 
#define  VIRTIO_IOMMU_S_IOERR 133 
#define  VIRTIO_IOMMU_S_NOENT 132 
#define  VIRTIO_IOMMU_S_NOMEM 131 
#define  VIRTIO_IOMMU_S_OK 130 
#define  VIRTIO_IOMMU_S_RANGE 129 
#define  VIRTIO_IOMMU_S_UNSUPP 128 

__attribute__((used)) static int viommu_get_req_errno(void *buf, size_t len)
{
	struct virtio_iommu_req_tail *tail = buf + len - sizeof(*tail);

	switch (tail->status) {
	case VIRTIO_IOMMU_S_OK:
		return 0;
	case VIRTIO_IOMMU_S_UNSUPP:
		return -ENOSYS;
	case VIRTIO_IOMMU_S_INVAL:
		return -EINVAL;
	case VIRTIO_IOMMU_S_RANGE:
		return -ERANGE;
	case VIRTIO_IOMMU_S_NOENT:
		return -ENOENT;
	case VIRTIO_IOMMU_S_FAULT:
		return -EFAULT;
	case VIRTIO_IOMMU_S_NOMEM:
		return -ENOMEM;
	case VIRTIO_IOMMU_S_IOERR:
	case VIRTIO_IOMMU_S_DEVERR:
	default:
		return -EIO;
	}
}