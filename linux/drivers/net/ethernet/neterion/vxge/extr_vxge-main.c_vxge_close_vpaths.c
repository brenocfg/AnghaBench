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
struct TYPE_2__ {int /*<<< orphan*/  vpaths_open; } ;
struct vxgedev {int no_of_vpath; TYPE_1__ stats; struct vxge_vpath* vpaths; } ;
struct vxge_vpath {int /*<<< orphan*/ * handle; scalar_t__ is_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  vxge_hw_vpath_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vxge_close_vpaths(struct vxgedev *vdev, int index)
{
	struct vxge_vpath *vpath;
	int i;

	for (i = index; i < vdev->no_of_vpath; i++) {
		vpath = &vdev->vpaths[i];

		if (vpath->handle && vpath->is_open) {
			vxge_hw_vpath_close(vpath->handle);
			vdev->stats.vpaths_open--;
		}
		vpath->is_open = 0;
		vpath->handle = NULL;
	}
}