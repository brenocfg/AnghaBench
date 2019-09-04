#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ intr_type; } ;
struct vxgedev {TYPE_1__ config; struct vxge_vpath* vpaths; } ;
struct vxge_vpath {int device_id; TYPE_4__* handle; } ;
struct TYPE_11__ {TYPE_3__* vpath; } ;
struct TYPE_10__ {TYPE_2__* hldev; } ;
struct TYPE_9__ {int first_vp_id; } ;

/* Variables and functions */
 scalar_t__ INTA ; 
 int VXGE_ALARM_MSIX_ID ; 
 int VXGE_HW_VPATH_MSIX_ACTIVE ; 
 int /*<<< orphan*/  vxge_hw_vpath_inta_unmask_tx_rx (TYPE_4__*) ; 
 int /*<<< orphan*/  vxge_hw_vpath_intr_enable (TYPE_4__*) ; 
 int /*<<< orphan*/  vxge_hw_vpath_msix_set (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  vxge_hw_vpath_msix_unmask (TYPE_4__*,int) ; 

__attribute__((used)) static void vxge_vpath_intr_enable(struct vxgedev *vdev, int vp_id)
{
	struct vxge_vpath *vpath = &vdev->vpaths[vp_id];
	int msix_id = 0;
	int tim_msix_id[4] = {0, 1, 0, 0};
	int alarm_msix_id = VXGE_ALARM_MSIX_ID;

	vxge_hw_vpath_intr_enable(vpath->handle);

	if (vdev->config.intr_type == INTA)
		vxge_hw_vpath_inta_unmask_tx_rx(vpath->handle);
	else {
		vxge_hw_vpath_msix_set(vpath->handle, tim_msix_id,
			alarm_msix_id);

		msix_id = vpath->device_id * VXGE_HW_VPATH_MSIX_ACTIVE;
		vxge_hw_vpath_msix_unmask(vpath->handle, msix_id);
		vxge_hw_vpath_msix_unmask(vpath->handle, msix_id + 1);

		/* enable the alarm vector */
		msix_id = (vpath->handle->vpath->hldev->first_vp_id *
			VXGE_HW_VPATH_MSIX_ACTIVE) + alarm_msix_id;
		vxge_hw_vpath_msix_unmask(vpath->handle, msix_id);
	}
}