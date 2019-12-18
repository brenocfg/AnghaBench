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
typedef  int u32 ;
struct amdgpu_ring {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int gds_reserve_size; int gds_reserve_addr; TYPE_1__* buf; } ;
struct TYPE_8__ {TYPE_3__ ngg; struct amdgpu_ring* gfx_ring; } ;
struct TYPE_6__ {scalar_t__ gds_size; } ;
struct amdgpu_device {TYPE_4__ gfx; TYPE_2__ gds; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  gpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE ; 
 int /*<<< orphan*/  BASE_HI ; 
 int /*<<< orphan*/  CNTL_SB_BUF_SIZE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  INDEX_BUF_SIZE ; 
 size_t NGG_CNTL ; 
 size_t NGG_PARAM ; 
 size_t NGG_POS ; 
 size_t NGG_PRIM ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_DMA_DATA ; 
 int PACKET3_DMA_DATA_CMD_RAW_WAIT ; 
 int PACKET3_DMA_DATA_CP_SYNC ; 
 int PACKET3_DMA_DATA_DST_SEL (int) ; 
 int PACKET3_DMA_DATA_SRC_SEL (int) ; 
 int /*<<< orphan*/  PARAM_BUF_SIZE ; 
 int /*<<< orphan*/  POS_BUF_SIZE ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WD_BUF_RESOURCE_1 ; 
 int /*<<< orphan*/  WD_BUF_RESOURCE_2 ; 
 int /*<<< orphan*/  WD_CNTL_SB_BUF_BASE ; 
 int /*<<< orphan*/  WD_CNTL_SB_BUF_BASE_HI ; 
 int /*<<< orphan*/  WD_INDEX_BUF_BASE ; 
 int /*<<< orphan*/  WD_INDEX_BUF_BASE_HI ; 
 int /*<<< orphan*/  WD_POS_BUF_BASE ; 
 int /*<<< orphan*/  WD_POS_BUF_BASE_HI ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_ngg ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_write_data_to_reg (struct amdgpu_ring*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmGDS_VMID0_SIZE ; 
 int /*<<< orphan*/  mmWD_BUF_RESOURCE_1 ; 
 int /*<<< orphan*/  mmWD_BUF_RESOURCE_2 ; 
 int /*<<< orphan*/  mmWD_CNTL_SB_BUF_BASE ; 
 int /*<<< orphan*/  mmWD_CNTL_SB_BUF_BASE_HI ; 
 int /*<<< orphan*/  mmWD_INDEX_BUF_BASE ; 
 int /*<<< orphan*/  mmWD_INDEX_BUF_BASE_HI ; 
 int /*<<< orphan*/  mmWD_POS_BUF_BASE ; 
 int /*<<< orphan*/  mmWD_POS_BUF_BASE_HI ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfx_v9_0_ngg_en(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = &adev->gfx.gfx_ring[0];
	int r;
	u32 data, base;

	if (!amdgpu_ngg)
		return 0;

	/* Program buffer size */
	data = REG_SET_FIELD(0, WD_BUF_RESOURCE_1, INDEX_BUF_SIZE,
			     adev->gfx.ngg.buf[NGG_PRIM].size >> 8);
	data = REG_SET_FIELD(data, WD_BUF_RESOURCE_1, POS_BUF_SIZE,
			     adev->gfx.ngg.buf[NGG_POS].size >> 8);
	WREG32_SOC15(GC, 0, mmWD_BUF_RESOURCE_1, data);

	data = REG_SET_FIELD(0, WD_BUF_RESOURCE_2, CNTL_SB_BUF_SIZE,
			     adev->gfx.ngg.buf[NGG_CNTL].size >> 8);
	data = REG_SET_FIELD(data, WD_BUF_RESOURCE_2, PARAM_BUF_SIZE,
			     adev->gfx.ngg.buf[NGG_PARAM].size >> 10);
	WREG32_SOC15(GC, 0, mmWD_BUF_RESOURCE_2, data);

	/* Program buffer base address */
	base = lower_32_bits(adev->gfx.ngg.buf[NGG_PRIM].gpu_addr);
	data = REG_SET_FIELD(0, WD_INDEX_BUF_BASE, BASE, base);
	WREG32_SOC15(GC, 0, mmWD_INDEX_BUF_BASE, data);

	base = upper_32_bits(adev->gfx.ngg.buf[NGG_PRIM].gpu_addr);
	data = REG_SET_FIELD(0, WD_INDEX_BUF_BASE_HI, BASE_HI, base);
	WREG32_SOC15(GC, 0, mmWD_INDEX_BUF_BASE_HI, data);

	base = lower_32_bits(adev->gfx.ngg.buf[NGG_POS].gpu_addr);
	data = REG_SET_FIELD(0, WD_POS_BUF_BASE, BASE, base);
	WREG32_SOC15(GC, 0, mmWD_POS_BUF_BASE, data);

	base = upper_32_bits(adev->gfx.ngg.buf[NGG_POS].gpu_addr);
	data = REG_SET_FIELD(0, WD_POS_BUF_BASE_HI, BASE_HI, base);
	WREG32_SOC15(GC, 0, mmWD_POS_BUF_BASE_HI, data);

	base = lower_32_bits(adev->gfx.ngg.buf[NGG_CNTL].gpu_addr);
	data = REG_SET_FIELD(0, WD_CNTL_SB_BUF_BASE, BASE, base);
	WREG32_SOC15(GC, 0, mmWD_CNTL_SB_BUF_BASE, data);

	base = upper_32_bits(adev->gfx.ngg.buf[NGG_CNTL].gpu_addr);
	data = REG_SET_FIELD(0, WD_CNTL_SB_BUF_BASE_HI, BASE_HI, base);
	WREG32_SOC15(GC, 0, mmWD_CNTL_SB_BUF_BASE_HI, data);

	/* Clear GDS reserved memory */
	r = amdgpu_ring_alloc(ring, 17);
	if (r) {
		DRM_ERROR("amdgpu: NGG failed to lock ring %s (%d).\n",
			  ring->name, r);
		return r;
	}

	gfx_v9_0_write_data_to_reg(ring, 0, false,
				   SOC15_REG_OFFSET(GC, 0, mmGDS_VMID0_SIZE),
			           (adev->gds.gds_size +
				    adev->gfx.ngg.gds_reserve_size));

	amdgpu_ring_write(ring, PACKET3(PACKET3_DMA_DATA, 5));
	amdgpu_ring_write(ring, (PACKET3_DMA_DATA_CP_SYNC |
				PACKET3_DMA_DATA_DST_SEL(1) |
				PACKET3_DMA_DATA_SRC_SEL(2)));
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, adev->gfx.ngg.gds_reserve_addr);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, PACKET3_DMA_DATA_CMD_RAW_WAIT |
				adev->gfx.ngg.gds_reserve_size);

	gfx_v9_0_write_data_to_reg(ring, 0, false,
				   SOC15_REG_OFFSET(GC, 0, mmGDS_VMID0_SIZE), 0);

	amdgpu_ring_commit(ring);

	return 0;
}