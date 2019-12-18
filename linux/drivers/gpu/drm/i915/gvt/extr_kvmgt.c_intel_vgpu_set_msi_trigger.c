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
typedef  int u32 ;
struct TYPE_2__ {struct eventfd_ctx* msi_trigger; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct eventfd_ctx*) ; 
 int PTR_ERR (struct eventfd_ctx*) ; 
 int VFIO_IRQ_SET_DATA_EVENTFD ; 
 int VFIO_IRQ_SET_DATA_NONE ; 
 struct eventfd_ctx* eventfd_ctx_fdget (int) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int /*<<< orphan*/  intel_vgpu_release_msi_eventfd_ctx (struct intel_vgpu*) ; 

__attribute__((used)) static int intel_vgpu_set_msi_trigger(struct intel_vgpu *vgpu,
		unsigned int index, unsigned int start, unsigned int count,
		u32 flags, void *data)
{
	struct eventfd_ctx *trigger;

	if (flags & VFIO_IRQ_SET_DATA_EVENTFD) {
		int fd = *(int *)data;

		trigger = eventfd_ctx_fdget(fd);
		if (IS_ERR(trigger)) {
			gvt_vgpu_err("eventfd_ctx_fdget failed\n");
			return PTR_ERR(trigger);
		}
		vgpu->vdev.msi_trigger = trigger;
	} else if ((flags & VFIO_IRQ_SET_DATA_NONE) && !count)
		intel_vgpu_release_msi_eventfd_ctx(vgpu);

	return 0;
}