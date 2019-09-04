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
struct TYPE_7__ {int total_size; int gfx_partition_size; int cs_partition_size; } ;
struct TYPE_6__ {int total_size; int gfx_partition_size; int cs_partition_size; } ;
struct TYPE_5__ {int total_size; int gfx_partition_size; int cs_partition_size; } ;
struct TYPE_8__ {TYPE_3__ oa; TYPE_2__ gws; TYPE_1__ mem; } ;
struct amdgpu_device {TYPE_4__ gds; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmGDS_VMID0_SIZE ; 

__attribute__((used)) static void gfx_v7_0_set_gds_init(struct amdgpu_device *adev)
{
	/* init asci gds info */
	adev->gds.mem.total_size = RREG32(mmGDS_VMID0_SIZE);
	adev->gds.gws.total_size = 64;
	adev->gds.oa.total_size = 16;

	if (adev->gds.mem.total_size == 64 * 1024) {
		adev->gds.mem.gfx_partition_size = 4096;
		adev->gds.mem.cs_partition_size = 4096;

		adev->gds.gws.gfx_partition_size = 4;
		adev->gds.gws.cs_partition_size = 4;

		adev->gds.oa.gfx_partition_size = 4;
		adev->gds.oa.cs_partition_size = 1;
	} else {
		adev->gds.mem.gfx_partition_size = 1024;
		adev->gds.mem.cs_partition_size = 1024;

		adev->gds.gws.gfx_partition_size = 16;
		adev->gds.gws.cs_partition_size = 16;

		adev->gds.oa.gfx_partition_size = 4;
		adev->gds.oa.cs_partition_size = 4;
	}
}