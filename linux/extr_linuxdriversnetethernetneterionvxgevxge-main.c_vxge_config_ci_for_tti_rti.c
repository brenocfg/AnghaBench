#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ intr_type; } ;
struct vxgedev {int no_of_vpath; TYPE_4__ config; TYPE_3__* vpaths; } ;
struct __vxge_hw_ring {int dummy; } ;
struct __vxge_hw_fifo {int dummy; } ;
struct TYPE_6__ {struct __vxge_hw_fifo* handle; } ;
struct TYPE_5__ {struct __vxge_hw_ring* handle; } ;
struct TYPE_7__ {TYPE_2__ fifo; TYPE_1__ ring; } ;

/* Variables and functions */
 scalar_t__ INTA ; 
 scalar_t__ MSI_X ; 
 int /*<<< orphan*/  vxge_hw_vpath_dynamic_rti_ci_set (struct __vxge_hw_ring*) ; 
 int /*<<< orphan*/  vxge_hw_vpath_tti_ci_set (struct __vxge_hw_fifo*) ; 

__attribute__((used)) static void vxge_config_ci_for_tti_rti(struct vxgedev *vdev)
{
	int i = 0;

	/* Enable CI for RTI */
	if (vdev->config.intr_type == MSI_X) {
		for (i = 0; i < vdev->no_of_vpath; i++) {
			struct __vxge_hw_ring *hw_ring;

			hw_ring = vdev->vpaths[i].ring.handle;
			vxge_hw_vpath_dynamic_rti_ci_set(hw_ring);
		}
	}

	/* Enable CI for TTI */
	for (i = 0; i < vdev->no_of_vpath; i++) {
		struct __vxge_hw_fifo *hw_fifo = vdev->vpaths[i].fifo.handle;
		vxge_hw_vpath_tti_ci_set(hw_fifo);
		/*
		 * For Inta (with or without napi), Set CI ON for only one
		 * vpath. (Have only one free running timer).
		 */
		if ((vdev->config.intr_type == INTA) && (i == 0))
			break;
	}

	return;
}