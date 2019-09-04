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
struct TYPE_2__ {struct eventfd_ctx* msi_trigger; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_ctx_put (struct eventfd_ctx*) ; 

__attribute__((used)) static void intel_vgpu_release_msi_eventfd_ctx(struct intel_vgpu *vgpu)
{
	struct eventfd_ctx *trigger;

	trigger = vgpu->vdev.msi_trigger;
	if (trigger) {
		eventfd_ctx_put(trigger);
		vgpu->vdev.msi_trigger = NULL;
	}
}