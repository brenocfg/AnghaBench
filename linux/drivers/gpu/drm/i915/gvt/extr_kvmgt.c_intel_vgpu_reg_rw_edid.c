#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ edid_offset; } ;
struct vfio_edid_region {TYPE_1__ vfio_edid_regs; } ;
struct TYPE_5__ {TYPE_3__* region; } ;
struct intel_vgpu {TYPE_2__ vdev; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ EDID_BLOB_OFFSET ; 
 unsigned int VFIO_PCI_NUM_REGIONS ; 
 scalar_t__ VFIO_PCI_OFFSET_MASK ; 
 unsigned int VFIO_PCI_OFFSET_TO_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int handle_edid_blob (struct vfio_edid_region*,char*,size_t,scalar_t__,int) ; 
 int handle_edid_regs (struct intel_vgpu*,struct vfio_edid_region*,char*,size_t,scalar_t__,int) ; 

__attribute__((used)) static size_t intel_vgpu_reg_rw_edid(struct intel_vgpu *vgpu, char *buf,
		size_t count, loff_t *ppos, bool iswrite)
{
	int ret;
	unsigned int i = VFIO_PCI_OFFSET_TO_INDEX(*ppos) -
			VFIO_PCI_NUM_REGIONS;
	struct vfio_edid_region *region =
		(struct vfio_edid_region *)vgpu->vdev.region[i].data;
	loff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;

	if (pos < region->vfio_edid_regs.edid_offset) {
		ret = handle_edid_regs(vgpu, region, buf, count, pos, iswrite);
	} else {
		pos -= EDID_BLOB_OFFSET;
		ret = handle_edid_blob(region, buf, count, pos, iswrite);
	}

	if (ret < 0)
		gvt_vgpu_err("failed to access EDID region\n");

	return ret;
}