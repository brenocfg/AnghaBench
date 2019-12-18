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
typedef  int u64 ;
struct virtio_iommu_probe_resv_mem {int subtype; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct viommu_endpoint {int /*<<< orphan*/  resv_regions; int /*<<< orphan*/  dev; } ;
struct iommu_resv_region {int /*<<< orphan*/  list; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOVERFLOW ; 
 unsigned long IOMMU_MMIO ; 
 unsigned long IOMMU_NOEXEC ; 
 int /*<<< orphan*/  IOMMU_RESV_MSI ; 
 int /*<<< orphan*/  IOMMU_RESV_RESERVED ; 
 unsigned long IOMMU_WRITE ; 
#define  VIRTIO_IOMMU_RESV_MEM_T_MSI 129 
#define  VIRTIO_IOMMU_RESV_MEM_T_RESERVED 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct iommu_resv_region* iommu_alloc_resv_region (int,size_t,unsigned long,int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viommu_add_resv_mem(struct viommu_endpoint *vdev,
			       struct virtio_iommu_probe_resv_mem *mem,
			       size_t len)
{
	size_t size;
	u64 start64, end64;
	phys_addr_t start, end;
	struct iommu_resv_region *region = NULL;
	unsigned long prot = IOMMU_WRITE | IOMMU_NOEXEC | IOMMU_MMIO;

	start = start64 = le64_to_cpu(mem->start);
	end = end64 = le64_to_cpu(mem->end);
	size = end64 - start64 + 1;

	/* Catch any overflow, including the unlikely end64 - start64 + 1 = 0 */
	if (start != start64 || end != end64 || size < end64 - start64)
		return -EOVERFLOW;

	if (len < sizeof(*mem))
		return -EINVAL;

	switch (mem->subtype) {
	default:
		dev_warn(vdev->dev, "unknown resv mem subtype 0x%x\n",
			 mem->subtype);
		/* Fall-through */
	case VIRTIO_IOMMU_RESV_MEM_T_RESERVED:
		region = iommu_alloc_resv_region(start, size, 0,
						 IOMMU_RESV_RESERVED);
		break;
	case VIRTIO_IOMMU_RESV_MEM_T_MSI:
		region = iommu_alloc_resv_region(start, size, prot,
						 IOMMU_RESV_MSI);
		break;
	}
	if (!region)
		return -ENOMEM;

	list_add(&vdev->resv_regions, &region->list);
	return 0;
}