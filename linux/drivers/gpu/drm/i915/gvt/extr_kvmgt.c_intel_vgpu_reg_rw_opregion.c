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
struct TYPE_3__ {TYPE_2__* region; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {scalar_t__ size; void* data; } ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned int VFIO_PCI_NUM_REGIONS ; 
 scalar_t__ VFIO_PCI_OFFSET_MASK ; 
 unsigned int VFIO_PCI_OFFSET_TO_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 size_t min (size_t,size_t) ; 

__attribute__((used)) static size_t intel_vgpu_reg_rw_opregion(struct intel_vgpu *vgpu, char *buf,
		size_t count, loff_t *ppos, bool iswrite)
{
	unsigned int i = VFIO_PCI_OFFSET_TO_INDEX(*ppos) -
			VFIO_PCI_NUM_REGIONS;
	void *base = vgpu->vdev.region[i].data;
	loff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;

	if (pos >= vgpu->vdev.region[i].size || iswrite) {
		gvt_vgpu_err("invalid op or offset for Intel vgpu OpRegion\n");
		return -EINVAL;
	}
	count = min(count, (size_t)(vgpu->vdev.region[i].size - pos));
	memcpy(buf, base + pos, count);

	return count;
}