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
typedef  int /*<<< orphan*/  u32 ;
struct vfio_region {unsigned int type; unsigned int subtype; size_t size; void* data; int /*<<< orphan*/  flags; struct intel_vgpu_regops const* ops; } ;
struct intel_vgpu_regops {int dummy; } ;
struct TYPE_2__ {int num_regions; struct vfio_region* region; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vfio_region* krealloc (struct vfio_region*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_vgpu_register_reg(struct intel_vgpu *vgpu,
		unsigned int type, unsigned int subtype,
		const struct intel_vgpu_regops *ops,
		size_t size, u32 flags, void *data)
{
	struct vfio_region *region;

	region = krealloc(vgpu->vdev.region,
			(vgpu->vdev.num_regions + 1) * sizeof(*region),
			GFP_KERNEL);
	if (!region)
		return -ENOMEM;

	vgpu->vdev.region = region;
	vgpu->vdev.region[vgpu->vdev.num_regions].type = type;
	vgpu->vdev.region[vgpu->vdev.num_regions].subtype = subtype;
	vgpu->vdev.region[vgpu->vdev.num_regions].ops = ops;
	vgpu->vdev.region[vgpu->vdev.num_regions].size = size;
	vgpu->vdev.region[vgpu->vdev.num_regions].flags = flags;
	vgpu->vdev.region[vgpu->vdev.num_regions].data = data;
	vgpu->vdev.num_regions++;
	return 0;
}