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
struct intel_vgpu {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mpt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* detach_vgpu ) (struct intel_vgpu*) ;} ;

/* Variables and functions */
 TYPE_2__ intel_gvt_host ; 
 int /*<<< orphan*/  stub1 (struct intel_vgpu*) ; 

__attribute__((used)) static inline void intel_gvt_hypervisor_detach_vgpu(struct intel_vgpu *vgpu)
{
	/* optional to provide */
	if (!intel_gvt_host.mpt->detach_vgpu)
		return;

	intel_gvt_host.mpt->detach_vgpu(vgpu);
}