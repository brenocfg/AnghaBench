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
struct vxgedev {int no_of_vpath; TYPE_1__* vpaths; } ;
struct TYPE_2__ {int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_COMPLETE_VPATH_TX (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void VXGE_COMPLETE_ALL_TX(struct vxgedev *vdev)
{
	int i;

	/* Complete all transmits */
	for (i = 0; i < vdev->no_of_vpath; i++)
		VXGE_COMPLETE_VPATH_TX(&vdev->vpaths[i].fifo);
}