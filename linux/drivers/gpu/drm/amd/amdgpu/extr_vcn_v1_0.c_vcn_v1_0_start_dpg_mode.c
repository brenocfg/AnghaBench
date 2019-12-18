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
typedef  int uint32_t ;
struct amdgpu_ring {int max_dw; void* wptr; void* gpu_addr; int /*<<< orphan*/  ring_size; } ;
struct TYPE_8__ {TYPE_3__* inst; } ;
struct TYPE_5__ {int gb_addr_config; } ;
struct TYPE_6__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_4__ vcn; TYPE_2__ gfx; } ;
struct TYPE_7__ {struct amdgpu_ring ring_jpeg; struct amdgpu_ring ring_dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_BLKSZ ; 
 int /*<<< orphan*/  RB_BUFSZ ; 
 int /*<<< orphan*/  RB_NO_FETCH ; 
 int /*<<< orphan*/  RB_NO_UPDATE ; 
 int /*<<< orphan*/  RB_RPTR_WR_EN ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int UVD_LMI_CTRL2__RE_OFLD_MIF_WR_REQ_NUM__SHIFT ; 
 int UVD_LMI_CTRL__CRC_RESET_MASK ; 
 int UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK ; 
 int UVD_LMI_CTRL__MASK_MC_URGENT_MASK ; 
 int UVD_LMI_CTRL__REQ_MODE_MASK ; 
 int UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK ; 
 int UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK ; 
 int UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT ; 
 int UVD_MASTINT_EN__VCPU_EN_MASK ; 
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
 int UVD_POWER_STATUS__UVD_PG_EN_MASK ; 
 int UVD_POWER_STATUS__UVD_PG_MODE_MASK ; 
 int /*<<< orphan*/  UVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK ; 
 int UVD_SYS_INT_EN__UVD_JRBC_EN_MASK ; 
 int UVD_VCPU_CNTL__CLK_EN_MASK ; 
 int UVD_VCPU_CNTL__MIF_WR_LOW_THRESHOLD_BP_MASK ; 
 int UVD_VCPU_CNTL__PRB_TIMEOUT_VAL__SHIFT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15_DPG_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int amdgpu_sched_hw_submission ; 
 int lower_32_bits (void*) ; 
 int /*<<< orphan*/  mmUVD_JPEG_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmUVD_JPEG_UV_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_RB_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_SWAP_CNTL ; 
 int /*<<< orphan*/  mmUVD_MASTINT_EN ; 
 int /*<<< orphan*/  mmUVD_MPC_CNTL ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUX ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXA0 ; 
 int /*<<< orphan*/  mmUVD_MPC_SET_MUXB0 ; 
 int /*<<< orphan*/  mmUVD_POWER_STATUS ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_RPTR_ADDR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR_CNTL ; 
 int /*<<< orphan*/  mmUVD_RBC_XX_IB_REG_CHECK ; 
 int /*<<< orphan*/  mmUVD_REG_XX_MASK ; 
 int /*<<< orphan*/  mmUVD_SCRATCH2 ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_SYS_INT_EN ; 
 int /*<<< orphan*/  mmUVD_VCPU_CNTL ; 
 int order_base_2 (int /*<<< orphan*/ ) ; 
 int upper_32_bits (void*) ; 
 int /*<<< orphan*/  vcn_1_0_enable_static_power_gating (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v1_0_clock_gating_dpg_mode (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  vcn_v1_0_jpeg_ring_set_patch_ring (struct amdgpu_ring*,void*) ; 
 int /*<<< orphan*/  vcn_v1_0_mc_resume_dpg_mode (struct amdgpu_device*) ; 

__attribute__((used)) static int vcn_v1_0_start_dpg_mode(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = &adev->vcn.inst->ring_dec;
	uint32_t rb_bufsz, tmp;
	uint32_t lmi_swap_cntl;

	/* disable byte swapping */
	lmi_swap_cntl = 0;

	vcn_1_0_enable_static_power_gating(adev);

	/* enable dynamic power gating mode */
	tmp = RREG32_SOC15(UVD, 0, mmUVD_POWER_STATUS);
	tmp |= UVD_POWER_STATUS__UVD_PG_MODE_MASK;
	tmp |= UVD_POWER_STATUS__UVD_PG_EN_MASK;
	WREG32_SOC15(UVD, 0, mmUVD_POWER_STATUS, tmp);

	/* enable clock gating */
	vcn_v1_0_clock_gating_dpg_mode(adev, 0);

	/* enable VCPU clock */
	tmp = (0xFF << UVD_VCPU_CNTL__PRB_TIMEOUT_VAL__SHIFT);
	tmp |= UVD_VCPU_CNTL__CLK_EN_MASK;
	tmp |= UVD_VCPU_CNTL__MIF_WR_LOW_THRESHOLD_BP_MASK;
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_VCPU_CNTL, tmp, 0xFFFFFFFF, 0);

	/* disable interupt */
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_MASTINT_EN,
			0, UVD_MASTINT_EN__VCPU_EN_MASK, 0);

	/* initialize VCN memory controller */
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_LMI_CTRL,
		(8 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
		UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
		UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__REQ_MODE_MASK |
		UVD_LMI_CTRL__CRC_RESET_MASK |
		UVD_LMI_CTRL__MASK_MC_URGENT_MASK |
		0x00100000L, 0xFFFFFFFF, 0);

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
#endif
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl, 0xFFFFFFFF, 0);

	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_MPC_CNTL,
		0x2 << UVD_MPC_CNTL__REPLACEMENT_MODE__SHIFT, 0xFFFFFFFF, 0);

	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_MPC_SET_MUXA0,
		((0x1 << UVD_MPC_SET_MUXA0__VARA_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXA0__VARA_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXA0__VARA_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXA0__VARA_4__SHIFT)), 0xFFFFFFFF, 0);

	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_MPC_SET_MUXB0,
		((0x1 << UVD_MPC_SET_MUXB0__VARB_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXB0__VARB_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXB0__VARB_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXB0__VARB_4__SHIFT)), 0xFFFFFFFF, 0);

	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_MPC_SET_MUX,
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)), 0xFFFFFFFF, 0);

	vcn_v1_0_mc_resume_dpg_mode(adev);

	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_REG_XX_MASK, 0x10, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_RBC_XX_IB_REG_CHECK, 0x3, 0xFFFFFFFF, 0);

	/* boot up the VCPU */
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_SOFT_RESET, 0, 0xFFFFFFFF, 0);

	/* enable UMC */
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_LMI_CTRL2,
		0x1F << UVD_LMI_CTRL2__RE_OFLD_MIF_WR_REQ_NUM__SHIFT,
		0xFFFFFFFF, 0);

	/* enable master interrupt */
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_MASTINT_EN,
			UVD_MASTINT_EN__VCPU_EN_MASK, UVD_MASTINT_EN__VCPU_EN_MASK, 0);

	vcn_v1_0_clock_gating_dpg_mode(adev, 1);
	/* setup mmUVD_LMI_CTRL */
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_LMI_CTRL,
		(8 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
		UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
		UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__REQ_MODE_MASK |
		UVD_LMI_CTRL__CRC_RESET_MASK |
		UVD_LMI_CTRL__MASK_MC_URGENT_MASK |
		0x00100000L, 0xFFFFFFFF, 1);

	tmp = adev->gfx.config.gb_addr_config;
	/* setup VCN global tiling registers */
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_JPEG_ADDR_CONFIG, tmp, 0xFFFFFFFF, 1);
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_JPEG_UV_ADDR_CONFIG, tmp, 0xFFFFFFFF, 1);

	/* enable System Interrupt for JRBC */
	WREG32_SOC15_DPG_MODE(UVD, 0, mmUVD_SYS_INT_EN,
									UVD_SYS_INT_EN__UVD_JRBC_EN_MASK, 0xFFFFFFFF, 1);

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

	/* initialize JPEG wptr */
	ring = &adev->vcn.inst->ring_jpeg;
	ring->wptr = RREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_WPTR);

	/* copy patch commands to the jpeg ring */
	vcn_v1_0_jpeg_ring_set_patch_ring(ring,
		(ring->wptr + ring->max_dw * amdgpu_sched_hw_submission));

	return 0;
}