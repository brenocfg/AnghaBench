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
typedef  int u32 ;
struct amdgpu_ring {int gpu_addr; int /*<<< orphan*/  ring_size; void* wptr; } ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 void* RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_UVD_CTX (int /*<<< orphan*/ ) ; 
 int SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK ; 
 int UVD_SOFT_RESET__LMI_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WREG32_UVD_CTX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixUVD_LMI_CACHE_CTRL ; 
 int lower_32_bits (void*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmSRBM_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_CGC_GATE ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_LMI_EXT40_ADDR ; 
 int /*<<< orphan*/  mmUVD_LMI_SWAP_CNTL ; 
 int /*<<< orphan*/  mmUVD_MASTINT_EN ; 
 int /*<<< orphan*/  mmUVD_MPC_CNTL ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_ALU ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUX ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXA0 ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXA1 ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXB0 ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXB1 ; 
 int /*<<< orphan*/  mmUVD_MP_SWAP_CNTL ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_BASE ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR_CNTL ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int /*<<< orphan*/  mmUVD_VCPU_CNTL ; 
 int order_base_2 (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 
 int /*<<< orphan*/  uvd_v4_2_mc_resume (struct amdgpu_device*) ; 
 int /*<<< orphan*/  uvd_v4_2_set_dcm (struct amdgpu_device*,int) ; 

__attribute__((used)) static int uvd_v4_2_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = &adev->uvd.inst->ring;
	uint32_t rb_bufsz;
	int i, j, r;
	u32 tmp;
	/* disable byte swapping */
	u32 lmi_swap_cntl = 0;
	u32 mp_swap_cntl = 0;

	/* set uvd busy */
	WREG32_P(mmUVD_STATUS, 1<<2, ~(1<<2));

	uvd_v4_2_set_dcm(adev, true);
	WREG32(mmUVD_CGC_GATE, 0);

	/* take UVD block out of reset */
	WREG32_P(mmSRBM_SOFT_RESET, 0, ~SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK);
	mdelay(5);

	/* enable VCPU clock */
	WREG32(mmUVD_VCPU_CNTL,  1 << 9);

	/* disable interupt */
	WREG32_P(mmUVD_MASTINT_EN, 0, ~(1 << 1));

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
	mp_swap_cntl = 0;
#endif
	WREG32(mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl);
	WREG32(mmUVD_MP_SWAP_CNTL, mp_swap_cntl);
	/* initialize UVD memory controller */
	WREG32(mmUVD_LMI_CTRL, 0x203108);

	tmp = RREG32(mmUVD_MPC_CNTL);
	WREG32(mmUVD_MPC_CNTL, tmp | 0x10);

	WREG32(mmUVD_MPC_SET_MUXA0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXA1, 0x0);
	WREG32(mmUVD_MPC_SET_MUXB0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXB1, 0x0);
	WREG32(mmUVD_MPC_SET_ALU, 0);
	WREG32(mmUVD_MPC_SET_MUX, 0x88);

	uvd_v4_2_mc_resume(adev);

	tmp = RREG32_UVD_CTX(ixUVD_LMI_CACHE_CTRL);
	WREG32_UVD_CTX(ixUVD_LMI_CACHE_CTRL, tmp & (~0x10));

	/* enable UMC */
	WREG32_P(mmUVD_LMI_CTRL2, 0, ~(1 << 8));

	WREG32_P(mmUVD_SOFT_RESET, 0, ~UVD_SOFT_RESET__LMI_SOFT_RESET_MASK);

	WREG32_P(mmUVD_SOFT_RESET, 0, ~UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);

	WREG32_P(mmUVD_SOFT_RESET, 0, ~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

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

	/* enable interupt */
	WREG32_P(mmUVD_MASTINT_EN, 3<<1, ~(3 << 1));

	WREG32_P(mmUVD_STATUS, 0, ~(1<<2));

	/* force RBC into idle state */
	WREG32(mmUVD_RBC_RB_CNTL, 0x11010101);

	/* Set the write pointer delay */
	WREG32(mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* programm the 4GB memory segment for rptr and ring buffer */
	WREG32(mmUVD_LMI_EXT40_ADDR, upper_32_bits(ring->gpu_addr) |
				   (0x7 << 16) | (0x1 << 31));

	/* Initialize the ring buffer's read and write pointers */
	WREG32(mmUVD_RBC_RB_RPTR, 0x0);

	ring->wptr = RREG32(mmUVD_RBC_RB_RPTR);
	WREG32(mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));

	/* set the ring address */
	WREG32(mmUVD_RBC_RB_BASE, ring->gpu_addr);

	/* Set ring buffer size */
	rb_bufsz = order_base_2(ring->ring_size);
	rb_bufsz = (0x1 << 8) | rb_bufsz;
	WREG32_P(mmUVD_RBC_RB_CNTL, rb_bufsz, ~0x11f1f);

	return 0;
}