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
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oa; int /*<<< orphan*/  gws; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  mem_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* amdgpu_gds_reg_offset ; 

__attribute__((used)) static void gfx_v8_0_init_gds_vmid(struct amdgpu_device *adev)
{
	int vmid;

	/*
	 * Initialize all compute and user-gfx VMIDs to have no GDS, GWS, or OA
	 * access. Compute VMIDs should be enabled by FW for target VMIDs,
	 * the driver can enable them for graphics. VMID0 should maintain
	 * access so that HWS firmware can save/restore entries.
	 */
	for (vmid = 1; vmid < 16; vmid++) {
		WREG32(amdgpu_gds_reg_offset[vmid].mem_base, 0);
		WREG32(amdgpu_gds_reg_offset[vmid].mem_size, 0);
		WREG32(amdgpu_gds_reg_offset[vmid].gws, 0);
		WREG32(amdgpu_gds_reg_offset[vmid].oa, 0);
	}
}