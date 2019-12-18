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
struct vxgedev {int no_of_vpath; TYPE_3__* vpaths; int /*<<< orphan*/  exec_mode; } ;
struct vxge_vpath {TYPE_2__* handle; struct vxgedev* vdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {TYPE_1__* vpath; } ;
struct TYPE_4__ {int vp_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int VXGE_ALARM_MSIX_ID ; 
 int /*<<< orphan*/  VXGE_DRIVER_NAME ; 
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_OK ; 
 int VXGE_HW_VPATH_MSIX_ACTIVE ; 
 int /*<<< orphan*/  vxge_debug_intr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int vxge_hw_vpath_alarm_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_vpath_msix_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vxge_hw_vpath_msix_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vxge_hw_vpath_msix_unmask (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t
vxge_alarm_msix_handle(int irq, void *dev_id)
{
	int i;
	enum vxge_hw_status status;
	struct vxge_vpath *vpath = (struct vxge_vpath *)dev_id;
	struct vxgedev *vdev = vpath->vdev;
	int msix_id = (vpath->handle->vpath->vp_id *
		VXGE_HW_VPATH_MSIX_ACTIVE) + VXGE_ALARM_MSIX_ID;

	for (i = 0; i < vdev->no_of_vpath; i++) {
		/* Reduce the chance of losing alarm interrupts by masking
		 * the vector. A pending bit will be set if an alarm is
		 * generated and on unmask the interrupt will be fired.
		 */
		vxge_hw_vpath_msix_mask(vdev->vpaths[i].handle, msix_id);
		vxge_hw_vpath_msix_clear(vdev->vpaths[i].handle, msix_id);

		status = vxge_hw_vpath_alarm_process(vdev->vpaths[i].handle,
			vdev->exec_mode);
		if (status == VXGE_HW_OK) {
			vxge_hw_vpath_msix_unmask(vdev->vpaths[i].handle,
						  msix_id);
			continue;
		}
		vxge_debug_intr(VXGE_ERR,
			"%s: vxge_hw_vpath_alarm_process failed %x ",
			VXGE_DRIVER_NAME, status);
	}
	return IRQ_HANDLED;
}