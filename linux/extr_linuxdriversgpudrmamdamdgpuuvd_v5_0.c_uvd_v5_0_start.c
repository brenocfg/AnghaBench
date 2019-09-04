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
typedef  int uint32_t ;
struct amdgpu_ring {void* wptr; void* gpu_addr; int /*<<< orphan*/  ring_size; } ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  RB_BLKSZ ; 
 int /*<<< orphan*/  RB_BUFSZ ; 
 int /*<<< orphan*/  RB_NO_FETCH ; 
 int /*<<< orphan*/  RB_NO_UPDATE ; 
 int /*<<< orphan*/  RB_RPTR_WR_EN ; 
 int /*<<< orphan*/  RB_WPTR_POLL_EN ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* RREG32 (int /*<<< orphan*/ ) ; 
 int SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK ; 
 int /*<<< orphan*/  UVD_RBC_RB_CNTL ; 
 int UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK ; 
 int UVD_SOFT_RESET__CSM_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__CXW_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LMI_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__RBC_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__TAP_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int lower_32_bits (void*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmSRBM_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_RB_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_SWAP_CNTL ; 
 int /*<<< orphan*/  mmUVD_MASTINT_EN ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_ALU ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUX ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXA0 ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXA1 ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXB0 ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXB1 ; 
 int /*<<< orphan*/  mmUVD_MP_SWAP_CNTL ; 
 int /*<<< orphan*/  mmUVD_POWER_STATUS ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_RPTR_ADDR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR_CNTL ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int /*<<< orphan*/  mmUVD_VCPU_CNTL ; 
 int order_base_2 (int /*<<< orphan*/ ) ; 
 int upper_32_bits (void*) ; 
 int /*<<< orphan*/  uvd_v5_0_mc_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v5_0_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = &adev->uvd.inst->ring;
	uint32_t rb_bufsz, tmp;
	uint32_t lmi_swap_cntl;
	uint32_t mp_swap_cntl;
	int i, j, r;

	/*disable DPG */
	WREG32_P(mmUVD_POWER_STATUS, 0, ~(1 << 2));

	/* disable byte swapping */
	lmi_swap_cntl = 0;
	mp_swap_cntl = 0;

	uvd_v5_0_mc_resume(adev);

	/* disable interupt */
	WREG32_P(mmUVD_MASTINT_EN, 0, ~(1 << 1));

	/* stall UMC and register bus before resetting VCPU */
	WREG32_P(mmUVD_LMI_CTRL2, 1 << 8, ~(1 << 8));
	mdelay(1);

	/* put LMI, VCPU, RBC etc... into reset */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__LMI_SOFT_RESET_MASK |
		UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK | UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK |
		UVD_SOFT_RESET__RBC_SOFT_RESET_MASK | UVD_SOFT_RESET__CSM_SOFT_RESET_MASK |
		UVD_SOFT_RESET__CXW_SOFT_RESET_MASK | UVD_SOFT_RESET__TAP_SOFT_RESET_MASK |
		UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);
	mdelay(5);

	/* take UVD block out of reset */
	WREG32_P(mmSRBM_SOFT_RESET, 0, ~SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK);
	mdelay(5);

	/* initialize UVD memory controller */
	WREG32(mmUVD_LMI_CTRL, 0x40 | (1 << 8) | (1 << 13) |
			     (1 << 21) | (1 << 9) | (1 << 20));

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
	mp_swap_cntl = 0;
#endif
	WREG32(mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl);
	WREG32(mmUVD_MP_SWAP_CNTL, mp_swap_cntl);

	WREG32(mmUVD_MPC_SET_MUXA0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXA1, 0x0);
	WREG32(mmUVD_MPC_SET_MUXB0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXB1, 0x0);
	WREG32(mmUVD_MPC_SET_ALU, 0);
	WREG32(mmUVD_MPC_SET_MUX, 0x88);

	/* take all subblocks out of reset, except VCPU */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
	mdelay(5);

	/* enable VCPU clock */
	WREG32(mmUVD_VCPU_CNTL,  1 << 9);

	/* enable UMC */
	WREG32_P(mmUVD_LMI_CTRL2, 0, ~(1 << 8));

	/* boot up the VCPU */
	WREG32(mmUVD_SOFT_RESET, 0);
	mdelay(10);

	for (i = 0; i < 10; ++i) {
		uint32_t status;
		for (j = 0; j < 100; ++j) {
			status = RREG32(mmUVD_STATUS);
			if (status & 2)
				break;
			mdelay(10);
		}
		r = 0;
		if (status & 2)
			break;

		DRM_ERROR("UVD not responding, trying to reset the VCPU!!!\n");
		WREG32_P(mmUVD_SOFT_RESET, UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK,
				~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(10);
		WREG32_P(mmUVD_SOFT_RESET, 0, ~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(10);
		r = -1;
	}

	if (r) {
		DRM_ERROR("UVD not responding, giving up!!!\n");
		return r;
	}
	/* enable master interrupt */
	WREG32_P(mmUVD_MASTINT_EN, 3 << 1, ~(3 << 1));

	/* clear the bit 4 of UVD_STATUS */
	WREG32_P(mmUVD_STATUS, 0, ~(2 << 1));

	rb_bufsz = order_base_2(ring->ring_size);
	tmp = 0;
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_WPTR_POLL_EN, 0);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
	/* force RBC into idle state */
	WREG32(mmUVD_RBC_RB_CNTL, tmp);

	/* set the write pointer delay */
	WREG32(mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* set the wb address */
	WREG32(mmUVD_RBC_RB_RPTR_ADDR, (upper_32_bits(ring->gpu_addr) >> 2));

	/* programm the RB_BASE for ring buffer */
	WREG32(mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
			lower_32_bits(ring->gpu_addr));
	WREG32(mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
			upper_32_bits(ring->gpu_addr));

	/* Initialize the ring buffer's read and write pointers */
	WREG32(mmUVD_RBC_RB_RPTR, 0);

	ring->wptr = RREG32(mmUVD_RBC_RB_RPTR);
	WREG32(mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));

	WREG32_P(mmUVD_RBC_RB_CNTL, 0, ~UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK);

	return 0;
}