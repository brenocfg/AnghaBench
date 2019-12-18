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
typedef  int /*<<< orphan*/  u32 ;
struct vfio_pci_regops {int dummy; } ;
struct vfio_pci_region {unsigned int type; unsigned int subtype; size_t size; void* data; int /*<<< orphan*/  flags; struct vfio_pci_regops const* ops; } ;
struct vfio_pci_device {int num_regions; struct vfio_pci_region* region; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vfio_pci_region* krealloc (struct vfio_pci_region*,int,int /*<<< orphan*/ ) ; 

int vfio_pci_register_dev_region(struct vfio_pci_device *vdev,
				 unsigned int type, unsigned int subtype,
				 const struct vfio_pci_regops *ops,
				 size_t size, u32 flags, void *data)
{
	struct vfio_pci_region *region;

	region = krealloc(vdev->region,
			  (vdev->num_regions + 1) * sizeof(*region),
			  GFP_KERNEL);
	if (!region)
		return -ENOMEM;

	vdev->region = region;
	vdev->region[vdev->num_regions].type = type;
	vdev->region[vdev->num_regions].subtype = subtype;
	vdev->region[vdev->num_regions].ops = ops;
	vdev->region[vdev->num_regions].size = size;
	vdev->region[vdev->num_regions].flags = flags;
	vdev->region[vdev->num_regions].data = data;

	vdev->num_regions++;

	return 0;
}