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
struct vxgedev {int no_of_vpath; struct vxge_vpath* vpaths; scalar_t__ intr_cnt; } ;
struct TYPE_4__ {int tx_vector_no; } ;
struct TYPE_3__ {int rx_vector_no; } ;
struct vxge_vpath {int device_id; int /*<<< orphan*/  handle; TYPE_2__ fifo; TYPE_1__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_ALARM_MSIX_ID ; 
 int VXGE_HW_VPATH_MSIX_ACTIVE ; 
 int vxge_alloc_msix (struct vxgedev*) ; 
 int /*<<< orphan*/  vxge_hw_vpath_msix_set (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxge_enable_msix(struct vxgedev *vdev)
{

	int i, ret = 0;
	/* 0 - Tx, 1 - Rx  */
	int tim_msix_id[4] = {0, 1, 0, 0};

	vdev->intr_cnt = 0;

	/* allocate msix vectors */
	ret = vxge_alloc_msix(vdev);
	if (!ret) {
		for (i = 0; i < vdev->no_of_vpath; i++) {
			struct vxge_vpath *vpath = &vdev->vpaths[i];

			/* If fifo or ring are not enabled, the MSIX vector for
			 * it should be set to 0.
			 */
			vpath->ring.rx_vector_no = (vpath->device_id *
						VXGE_HW_VPATH_MSIX_ACTIVE) + 1;

			vpath->fifo.tx_vector_no = (vpath->device_id *
						VXGE_HW_VPATH_MSIX_ACTIVE);

			vxge_hw_vpath_msix_set(vpath->handle, tim_msix_id,
					       VXGE_ALARM_MSIX_ID);
		}
	}

	return ret;
}