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
struct amdgpu_ring {int ring_size; int gpu_addr; int wptr; int max_dw; } ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ vcn; } ;
struct TYPE_3__ {struct amdgpu_ring ring_jpeg; struct amdgpu_ring* ring_enc; struct amdgpu_ring ring_dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  RB_BLKSZ ; 
 int /*<<< orphan*/  RB_BUFSZ ; 
 int /*<<< orphan*/  RB_NO_FETCH ; 
 int /*<<< orphan*/  RB_NO_UPDATE ; 
 int /*<<< orphan*/  RB_RPTR_WR_EN ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int UVD_JRBC_RB_CNTL__RB_NO_FETCH_MASK ; 
 int UVD_JRBC_RB_CNTL__RB_RPTR_WR_EN_MASK ; 
 int /*<<< orphan*/  UVD_LMI_CTRL2__STALL_ARB_UMC_MASK ; 
 int UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK ; 
 int UVD_LMI_CTRL__MASK_MC_URGENT_MASK ; 
 int UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK ; 
 int UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK ; 
 int /*<<< orphan*/  UVD_MASTINT_EN__VCPU_EN_MASK ; 
 int UVD_MPC_CNTL__REPLACEMENT_MODE_MASK ; 
 int UVD_MPC_CNTL__REPLACEMENT_MODE__SHIFT ; 
 int UVD_MPC_SET_MUXA0__VARA_1__SHIFT ; 
 int UVD_MPC_SET_MUXA0__VARA_2__SHIFT ; 
 int UVD_MPC_SET_MUXA0__VARA_3__SHIFT ; 
 int UVD_MPC_SET_MUXA0__VARA_4__SHIFT ; 
 int UVD_MPC_SET_MUXB0__VARB_1__SHIFT ; 
 int UVD_MPC_SET_MUXB0__VARB_2__SHIFT ; 
 int UVD_MPC_SET_MUXB0__VARB_3__SHIFT ; 
 int UVD_MPC_SET_MUXB0__VARB_4__SHIFT ; 
 int UVD_MPC_SET_MUX__SET_0__SHIFT ; 
 int UVD_MPC_SET_MUX__SET_1__SHIFT ; 
 int UVD_MPC_SET_MUX__SET_2__SHIFT ; 
 int /*<<< orphan*/  UVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK ; 
 int UVD_SOFT_RESET__LMI_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK ; 
 int UVD_STATUS__IDLE ; 
 int UVD_STATUS__UVD_BUSY ; 
 int /*<<< orphan*/  UVD_SYS_INT_EN__UVD_JRBC_EN_MASK ; 
 int UVD_VCPU_CNTL__CLK_EN_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int amdgpu_sched_hw_submission ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_VMID ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_RB_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_SWAP_CNTL ; 
 int /*<<< orphan*/  mmUVD_MASTINT_EN ; 
 int /*<<< orphan*/  mmUVD_MPC_CNTL ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUX ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXA0 ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXB0 ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_RPTR_ADDR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR_CNTL ; 
 int /*<<< orphan*/  mmUVD_RBC_XX_IB_REG_CHECK ; 
 int /*<<< orphan*/  mmUVD_RB_BASE_HI ; 
 int /*<<< orphan*/  mmUVD_RB_BASE_HI2 ; 
 int /*<<< orphan*/  mmUVD_RB_BASE_LO ; 
 int /*<<< orphan*/  mmUVD_RB_BASE_LO2 ; 
 int /*<<< orphan*/  mmUVD_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_RB_RPTR2 ; 
 int /*<<< orphan*/  mmUVD_RB_SIZE ; 
 int /*<<< orphan*/  mmUVD_RB_SIZE2 ; 
 int /*<<< orphan*/  mmUVD_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RB_WPTR2 ; 
 int /*<<< orphan*/  mmUVD_REG_XX_MASK ; 
 int /*<<< orphan*/  mmUVD_SCRATCH2 ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int /*<<< orphan*/  mmUVD_SYS_INT_EN ; 
 int /*<<< orphan*/  mmUVD_VCPU_CNTL ; 
 int order_base_2 (int) ; 
 int upper_32_bits (int) ; 
 int /*<<< orphan*/  vcn_1_0_disable_static_power_gating (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v1_0_disable_clock_gating (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v1_0_jpeg_ring_set_patch_ring (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  vcn_v1_0_mc_resume_spg_mode (struct amdgpu_device*) ; 

__attribute__((used)) static int vcn_v1_0_start_spg_mode(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = &adev->vcn.inst->ring_dec;
	uint32_t rb_bufsz, tmp;
	uint32_t lmi_swap_cntl;
	int i, j, r;

	/* disable byte swapping */
	lmi_swap_cntl = 0;

	vcn_1_0_disable_static_power_gating(adev);

	tmp = RREG32_SOC15(UVD, 0, mmUVD_STATUS) | UVD_STATUS__UVD_BUSY;
	WREG32_SOC15(UVD, 0, mmUVD_STATUS, tmp);

	/* disable clock gating */
	vcn_v1_0_disable_clock_gating(adev);

	/* disable interupt */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_MASTINT_EN), 0,
			~UVD_MASTINT_EN__VCPU_EN_MASK);

	/* initialize VCN memory controller */
	tmp = RREG32_SOC15(UVD, 0, mmUVD_LMI_CTRL);
	WREG32_SOC15(UVD, 0, mmUVD_LMI_CTRL, tmp		|
		UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK	|
		UVD_LMI_CTRL__MASK_MC_URGENT_MASK			|
		UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK		|
		UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK);

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
#endif
	WREG32_SOC15(UVD, 0, mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl);

	tmp = RREG32_SOC15(UVD, 0, mmUVD_MPC_CNTL);
	tmp &= ~UVD_MPC_CNTL__REPLACEMENT_MODE_MASK;
	tmp |= 0x2 << UVD_MPC_CNTL__REPLACEMENT_MODE__SHIFT;
	WREG32_SOC15(UVD, 0, mmUVD_MPC_CNTL, tmp);

	WREG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUXA0,
		((0x1 << UVD_MPC_SET_MUXA0__VARA_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUXA0__VARA_2__SHIFT) |
		(0x3 << UVD_MPC_SET_MUXA0__VARA_3__SHIFT) |
		(0x4 << UVD_MPC_SET_MUXA0__VARA_4__SHIFT)));

	WREG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUXB0,
		((0x1 << UVD_MPC_SET_MUXB0__VARB_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUXB0__VARB_2__SHIFT) |
		(0x3 << UVD_MPC_SET_MUXB0__VARB_3__SHIFT) |
		(0x4 << UVD_MPC_SET_MUXB0__VARB_4__SHIFT)));

	WREG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUX,
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		(0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)));

	vcn_v1_0_mc_resume_spg_mode(adev);

	WREG32_SOC15(UVD, 0, mmUVD_REG_XX_MASK, 0x10);
	WREG32_SOC15(UVD, 0, mmUVD_RBC_XX_IB_REG_CHECK,
		RREG32_SOC15(UVD, 0, mmUVD_RBC_XX_IB_REG_CHECK) | 0x3);

	/* enable VCPU clock */
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CNTL, UVD_VCPU_CNTL__CLK_EN_MASK);

	/* boot up the VCPU */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET), 0,
			~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

	/* enable UMC */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_CTRL2), 0,
			~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);

	tmp = RREG32_SOC15(UVD, 0, mmUVD_SOFT_RESET);
	tmp &= ~UVD_SOFT_RESET__LMI_SOFT_RESET_MASK;
	tmp &= ~UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK;
	WREG32_SOC15(UVD, 0, mmUVD_SOFT_RESET, tmp);

	for (i = 0; i < 10; ++i) {
		uint32_t status;

		for (j = 0; j < 100; ++j) {
			status = RREG32_SOC15(UVD, 0, mmUVD_STATUS);
			if (status & UVD_STATUS__IDLE)
				break;
			mdelay(10);
		}
		r = 0;
		if (status & UVD_STATUS__IDLE)
			break;

		DRM_ERROR("VCN decode not responding, trying to reset the VCPU!!!\n");
		WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
				UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK,
				~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(10);
		WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET), 0,
				~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(10);
		r = -1;
	}

	if (r) {
		DRM_ERROR("VCN decode not responding, giving up!!!\n");
		return r;
	}
	/* enable master interrupt */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_MASTINT_EN),
		UVD_MASTINT_EN__VCPU_EN_MASK, ~UVD_MASTINT_EN__VCPU_EN_MASK);

	/* enable system interrupt for JRBC, TODO: move to set interrupt*/
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SYS_INT_EN),
		UVD_SYS_INT_EN__UVD_JRBC_EN_MASK,
		~UVD_SYS_INT_EN__UVD_JRBC_EN_MASK);

	/* clear the busy bit of UVD_STATUS */
	tmp = RREG32_SOC15(UVD, 0, mmUVD_STATUS) & ~UVD_STATUS__UVD_BUSY;
	WREG32_SOC15(UVD, 0, mmUVD_STATUS, tmp);

	/* force RBC into idle state */
	rb_bufsz = order_base_2(ring->ring_size);
	tmp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
	tmp = REG_SET_FIELD(tmp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_CNTL, tmp);

	/* set the write pointer delay */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* set the wb address */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR_ADDR,
			(upper_32_bits(ring->gpu_addr) >> 2));

	/* programm the RB_BASE for ring buffer */
	WREG32_SOC15(UVD, 0, mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
			lower_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
			upper_32_bits(ring->gpu_addr));

	/* Initialize the ring buffer's read and write pointers */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR, 0);

	WREG32_SOC15(UVD, 0, mmUVD_SCRATCH2, 0);

	ring->wptr = RREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR);
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR,
			lower_32_bits(ring->wptr));

	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_RBC_RB_CNTL), 0,
			~UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK);

	ring = &adev->vcn.inst->ring_enc[0];
	WREG32_SOC15(UVD, 0, mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_LO, ring->gpu_addr);
	WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_SIZE, ring->ring_size / 4);

	ring = &adev->vcn.inst->ring_enc[1];
	WREG32_SOC15(UVD, 0, mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_LO2, ring->gpu_addr);
	WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_SIZE2, ring->ring_size / 4);

	ring = &adev->vcn.inst->ring_jpeg;
	WREG32_SOC15(UVD, 0, mmUVD_LMI_JRBC_RB_VMID, 0);
	WREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_CNTL, UVD_JRBC_RB_CNTL__RB_NO_FETCH_MASK |
			UVD_JRBC_RB_CNTL__RB_RPTR_WR_EN_MASK);
	WREG32_SOC15(UVD, 0, mmUVD_LMI_JRBC_RB_64BIT_BAR_LOW, lower_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_LMI_JRBC_RB_64BIT_BAR_HIGH, upper_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_RPTR, 0);
	WREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_WPTR, 0);
	WREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_CNTL, UVD_JRBC_RB_CNTL__RB_RPTR_WR_EN_MASK);

	/* initialize wptr */
	ring->wptr = RREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_WPTR);

	/* copy patch commands to the jpeg ring */
	vcn_v1_0_jpeg_ring_set_patch_ring(ring,
		(ring->wptr + ring->max_dw * amdgpu_sched_hw_submission));

	return 0;
}