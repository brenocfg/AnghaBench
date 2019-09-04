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
struct intel_vgpu {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {TYPE_1__* mpt; } ;
struct TYPE_3__ {int (* enable_page_track ) (int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 TYPE_2__ intel_gvt_host ; 
 int stub1 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline int intel_gvt_hypervisor_enable_page_track(
		struct intel_vgpu *vgpu, unsigned long gfn)
{
	return intel_gvt_host.mpt->enable_page_track(vgpu->handle, gfn);
}