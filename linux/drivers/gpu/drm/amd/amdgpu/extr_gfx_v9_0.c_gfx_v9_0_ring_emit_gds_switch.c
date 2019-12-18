#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int GDS_GWS_VMID0__SIZE__SHIFT ; 
 scalar_t__ SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v9_0_write_data_to_reg (struct amdgpu_ring*,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  mmGDS_GWS_VMID0 ; 
 int /*<<< orphan*/  mmGDS_OA_VMID0 ; 
 int /*<<< orphan*/  mmGDS_VMID0_BASE ; 
 int /*<<< orphan*/  mmGDS_VMID0_SIZE ; 

__attribute__((used)) static void gfx_v9_0_ring_emit_gds_switch(struct amdgpu_ring *ring,
					  uint32_t vmid,
					  uint32_t gds_base, uint32_t gds_size,
					  uint32_t gws_base, uint32_t gws_size,
					  uint32_t oa_base, uint32_t oa_size)
{
	struct amdgpu_device *adev = ring->adev;

	/* GDS Base */
	gfx_v9_0_write_data_to_reg(ring, 0, false,
				   SOC15_REG_OFFSET(GC, 0, mmGDS_VMID0_BASE) + 2 * vmid,
				   gds_base);

	/* GDS Size */
	gfx_v9_0_write_data_to_reg(ring, 0, false,
				   SOC15_REG_OFFSET(GC, 0, mmGDS_VMID0_SIZE) + 2 * vmid,
				   gds_size);

	/* GWS */
	gfx_v9_0_write_data_to_reg(ring, 0, false,
				   SOC15_REG_OFFSET(GC, 0, mmGDS_GWS_VMID0) + vmid,
				   gws_size << GDS_GWS_VMID0__SIZE__SHIFT | gws_base);

	/* OA */
	gfx_v9_0_write_data_to_reg(ring, 0, false,
				   SOC15_REG_OFFSET(GC, 0, mmGDS_OA_VMID0) + vmid,
				   (1 << (oa_size + oa_base)) - (1 << oa_base));
}