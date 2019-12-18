#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct amdgpu_ih_ring {int gpu_addr; scalar_t__ ring_size; int /*<<< orphan*/  wptr_addr; scalar_t__ use_bus_addr; } ;
struct TYPE_6__ {struct amdgpu_ih_ring ih2; struct amdgpu_ih_ring ih1; int /*<<< orphan*/  msi_enabled; struct amdgpu_ih_ring ih; } ;
struct TYPE_5__ {scalar_t__ load_type; } ;
struct amdgpu_device {scalar_t__ asic_type; int /*<<< orphan*/  pdev; int /*<<< orphan*/  psp; TYPE_3__ irq; TYPE_2__ firmware; TYPE_1__* nbio_funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ih_control ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 scalar_t__ CHIP_ARCTURUS ; 
 scalar_t__ CHIP_RENOIR ; 
 int /*<<< orphan*/  CLIENT18_IS_STORM_CLIENT ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FLOOD_CNTL_ENABLE ; 
 int /*<<< orphan*/  IH_CHICKEN ; 
 int /*<<< orphan*/  IH_INT_FLOOD_CNTL ; 
 int /*<<< orphan*/  IH_RB_CNTL ; 
 int /*<<< orphan*/  IH_STORM_CLIENT_LIST_CNTL ; 
 int /*<<< orphan*/  MC_SPACE_FBPA_ENABLE ; 
 int /*<<< orphan*/  MC_SPACE_GPA_ENABLE ; 
 int /*<<< orphan*/  OSSSYS ; 
 int /*<<< orphan*/  PSP_REG_IH_RB_CNTL ; 
 int /*<<< orphan*/  PSP_REG_IH_RB_CNTL_RING1 ; 
 int /*<<< orphan*/  PSP_REG_IH_RB_CNTL_RING2 ; 
 int /*<<< orphan*/  RB_FULL_DRAIN_ENABLE ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RPTR_REARM ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPTR_OVERFLOW_ENABLE ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmIH_CHICKEN ; 
 int /*<<< orphan*/  mmIH_DOORBELL_RPTR ; 
 int /*<<< orphan*/  mmIH_DOORBELL_RPTR_RING1 ; 
 int /*<<< orphan*/  mmIH_DOORBELL_RPTR_RING2 ; 
 int /*<<< orphan*/  mmIH_INT_FLOOD_CNTL ; 
 int /*<<< orphan*/  mmIH_RB_BASE ; 
 int /*<<< orphan*/  mmIH_RB_BASE_HI ; 
 int /*<<< orphan*/  mmIH_RB_BASE_HI_RING1 ; 
 int /*<<< orphan*/  mmIH_RB_BASE_HI_RING2 ; 
 int /*<<< orphan*/  mmIH_RB_BASE_RING1 ; 
 int /*<<< orphan*/  mmIH_RB_BASE_RING2 ; 
 int /*<<< orphan*/  mmIH_RB_CNTL ; 
 int /*<<< orphan*/  mmIH_RB_CNTL_RING1 ; 
 int /*<<< orphan*/  mmIH_RB_CNTL_RING2 ; 
 int /*<<< orphan*/  mmIH_RB_RPTR ; 
 int /*<<< orphan*/  mmIH_RB_RPTR_RING1 ; 
 int /*<<< orphan*/  mmIH_RB_RPTR_RING2 ; 
 int /*<<< orphan*/  mmIH_RB_WPTR ; 
 int /*<<< orphan*/  mmIH_RB_WPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmIH_RB_WPTR_ADDR_LO ; 
 int /*<<< orphan*/  mmIH_RB_WPTR_RING1 ; 
 int /*<<< orphan*/  mmIH_RB_WPTR_RING2 ; 
 int /*<<< orphan*/  mmIH_STORM_CLIENT_LIST_CNTL ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 scalar_t__ psp_reg_program (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega10_ih_disable_interrupts (struct amdgpu_device*) ; 
 int vega10_ih_doorbell_rptr (struct amdgpu_ih_ring*) ; 
 int /*<<< orphan*/  vega10_ih_enable_interrupts (struct amdgpu_device*) ; 
 int vega10_ih_rb_cntl (struct amdgpu_ih_ring*,int) ; 

__attribute__((used)) static int vega10_ih_irq_init(struct amdgpu_device *adev)
{
	struct amdgpu_ih_ring *ih;
	u32 ih_rb_cntl, ih_chicken;
	int ret = 0;
	u32 tmp;

	/* disable irqs */
	vega10_ih_disable_interrupts(adev);

	adev->nbio_funcs->ih_control(adev);

	ih = &adev->irq.ih;
	/* Ring Buffer base. [39:8] of 40-bit address of the beginning of the ring buffer*/
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE, ih->gpu_addr >> 8);
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE_HI, (ih->gpu_addr >> 40) & 0xff);

	ih_rb_cntl = RREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL);
	ih_chicken = RREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN);
	ih_rb_cntl = vega10_ih_rb_cntl(ih, ih_rb_cntl);
	if (adev->irq.ih.use_bus_addr) {
		ih_chicken = REG_SET_FIELD(ih_chicken, IH_CHICKEN, MC_SPACE_GPA_ENABLE, 1);
	} else {
		ih_chicken = REG_SET_FIELD(ih_chicken, IH_CHICKEN, MC_SPACE_FBPA_ENABLE, 1);
	}
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RPTR_REARM,
				   !!adev->irq.msi_enabled);

	if (amdgpu_sriov_vf(adev)) {
		if (psp_reg_program(&adev->psp, PSP_REG_IH_RB_CNTL, ih_rb_cntl)) {
			DRM_ERROR("PSP program IH_RB_CNTL failed!\n");
			return -ETIMEDOUT;
		}
	} else {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL, ih_rb_cntl);
	}

	if ((adev->asic_type == CHIP_ARCTURUS
		&& adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT)
		|| adev->asic_type == CHIP_RENOIR)
		WREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN, ih_chicken);

	/* set the writeback address whether it's enabled or not */
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR_ADDR_LO,
		     lower_32_bits(ih->wptr_addr));
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR_ADDR_HI,
		     upper_32_bits(ih->wptr_addr) & 0xFFFF);

	/* set rptr, wptr to 0 */
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR, 0);
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR, 0);

	WREG32_SOC15(OSSSYS, 0, mmIH_DOORBELL_RPTR,
		     vega10_ih_doorbell_rptr(ih));

	ih = &adev->irq.ih1;
	if (ih->ring_size) {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE_RING1, ih->gpu_addr >> 8);
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE_HI_RING1,
			     (ih->gpu_addr >> 40) & 0xff);

		ih_rb_cntl = RREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL_RING1);
		ih_rb_cntl = vega10_ih_rb_cntl(ih, ih_rb_cntl);
		ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL,
					   WPTR_OVERFLOW_ENABLE, 0);
		ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL,
					   RB_FULL_DRAIN_ENABLE, 1);
		if (amdgpu_sriov_vf(adev)) {
			if (psp_reg_program(&adev->psp, PSP_REG_IH_RB_CNTL_RING1,
						ih_rb_cntl)) {
				DRM_ERROR("program IH_RB_CNTL_RING1 failed!\n");
				return -ETIMEDOUT;
			}
		} else {
			WREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL_RING1, ih_rb_cntl);
		}

		/* set rptr, wptr to 0 */
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR_RING1, 0);
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR_RING1, 0);

		WREG32_SOC15(OSSSYS, 0, mmIH_DOORBELL_RPTR_RING1,
			     vega10_ih_doorbell_rptr(ih));
	}

	ih = &adev->irq.ih2;
	if (ih->ring_size) {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE_RING2, ih->gpu_addr >> 8);
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE_HI_RING2,
			     (ih->gpu_addr >> 40) & 0xff);

		ih_rb_cntl = RREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL_RING2);
		ih_rb_cntl = vega10_ih_rb_cntl(ih, ih_rb_cntl);

		if (amdgpu_sriov_vf(adev)) {
			if (psp_reg_program(&adev->psp, PSP_REG_IH_RB_CNTL_RING2,
						ih_rb_cntl)) {
				DRM_ERROR("program IH_RB_CNTL_RING2 failed!\n");
				return -ETIMEDOUT;
			}
		} else {
			WREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL_RING2, ih_rb_cntl);
		}

		/* set rptr, wptr to 0 */
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR_RING2, 0);
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR_RING2, 0);

		WREG32_SOC15(OSSSYS, 0, mmIH_DOORBELL_RPTR_RING2,
			     vega10_ih_doorbell_rptr(ih));
	}

	tmp = RREG32_SOC15(OSSSYS, 0, mmIH_STORM_CLIENT_LIST_CNTL);
	tmp = REG_SET_FIELD(tmp, IH_STORM_CLIENT_LIST_CNTL,
			    CLIENT18_IS_STORM_CLIENT, 1);
	WREG32_SOC15(OSSSYS, 0, mmIH_STORM_CLIENT_LIST_CNTL, tmp);

	tmp = RREG32_SOC15(OSSSYS, 0, mmIH_INT_FLOOD_CNTL);
	tmp = REG_SET_FIELD(tmp, IH_INT_FLOOD_CNTL, FLOOD_CNTL_ENABLE, 1);
	WREG32_SOC15(OSSSYS, 0, mmIH_INT_FLOOD_CNTL, tmp);

	pci_set_master(adev->pdev);

	/* enable interrupts */
	vega10_ih_enable_interrupts(adev);

	return ret;
}