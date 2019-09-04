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
typedef  int /*<<< orphan*/  u64 ;
struct intel_vgpu {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {TYPE_1__* mpt; } ;
struct TYPE_3__ {int (* set_trap_area ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_2__ intel_gvt_host ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int intel_gvt_hypervisor_set_trap_area(
		struct intel_vgpu *vgpu, u64 start, u64 end, bool map)
{
	/* a MPT implementation could have MMIO trapped elsewhere */
	if (!intel_gvt_host.mpt->set_trap_area)
		return 0;

	return intel_gvt_host.mpt->set_trap_area(vgpu->handle, start, end, map);
}