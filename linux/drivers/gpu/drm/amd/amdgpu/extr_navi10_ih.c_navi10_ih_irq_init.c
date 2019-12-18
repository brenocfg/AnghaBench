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
struct amdgpu_ih_ring {int gpu_addr; int doorbell_index; scalar_t__ use_doorbell; int /*<<< orphan*/  wptr_addr; scalar_t__ use_bus_addr; } ;
struct TYPE_5__ {scalar_t__ load_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  msi_enabled; struct amdgpu_ih_ring ih; } ;
struct amdgpu_device {int /*<<< orphan*/  pdev; TYPE_3__* nbio_funcs; TYPE_2__ firmware; TYPE_1__ irq; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ih_doorbell_range ) (struct amdgpu_device*,scalar_t__,int) ;int /*<<< orphan*/  (* ih_control ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  CLIENT18_IS_STORM_CLIENT ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  FLOOD_CNTL_ENABLE ; 
 int /*<<< orphan*/  IH_CHICKEN ; 
 int /*<<< orphan*/  IH_DOORBELL_RPTR ; 
 int /*<<< orphan*/  IH_INT_FLOOD_CNTL ; 
 int /*<<< orphan*/  IH_RB_CNTL ; 
 int /*<<< orphan*/  IH_STORM_CLIENT_LIST_CNTL ; 
 int /*<<< orphan*/  MC_SPACE_GPA_ENABLE ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  OSSSYS ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RPTR_REARM ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmIH_CHICKEN ; 
 int /*<<< orphan*/  mmIH_DOORBELL_RPTR ; 
 int /*<<< orphan*/  mmIH_INT_FLOOD_CNTL ; 
 int /*<<< orphan*/  mmIH_RB_BASE ; 
 int /*<<< orphan*/  mmIH_RB_BASE_HI ; 
 int /*<<< orphan*/  mmIH_RB_CNTL ; 
 int /*<<< orphan*/  mmIH_RB_RPTR ; 
 int /*<<< orphan*/  mmIH_RB_WPTR ; 
 int /*<<< orphan*/  mmIH_RB_WPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmIH_RB_WPTR_ADDR_LO ; 
 int /*<<< orphan*/  mmIH_STORM_CLIENT_LIST_CNTL ; 
 int /*<<< orphan*/  navi10_ih_disable_interrupts (struct amdgpu_device*) ; 
 int /*<<< orphan*/  navi10_ih_enable_interrupts (struct amdgpu_device*) ; 
 int navi10_ih_rb_cntl (struct amdgpu_ih_ring*,int) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*,scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int navi10_ih_irq_init(struct amdgpu_device *adev)
{
	struct amdgpu_ih_ring *ih = &adev->irq.ih;
	int ret = 0;
	u32 ih_rb_cntl, ih_doorbell_rtpr, ih_chicken;
	u32 tmp;

	/* disable irqs */
	navi10_ih_disable_interrupts(adev);

	adev->nbio_funcs->ih_control(adev);

	/* Ring Buffer base. [39:8] of 40-bit address of the beginning of the ring buffer*/
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE, ih->gpu_addr >> 8);
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE_HI, (ih->gpu_addr >> 40) & 0xff);

	ih_rb_cntl = RREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL);
	ih_rb_cntl = navi10_ih_rb_cntl(ih, ih_rb_cntl);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RPTR_REARM,
				   !!adev->irq.msi_enabled);

	if (unlikely(adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT)) {
		if (ih->use_bus_addr) {
			ih_chicken = RREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN);
			ih_chicken = REG_SET_FIELD(ih_chicken,
					IH_CHICKEN, MC_SPACE_GPA_ENABLE, 1);
			WREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN, ih_chicken);
		}
	}

	WREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL, ih_rb_cntl);

	/* set the writeback address whether it's enabled or not */
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR_ADDR_LO,
		     lower_32_bits(ih->wptr_addr));
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR_ADDR_HI,
		     upper_32_bits(ih->wptr_addr) & 0xFFFF);

	/* set rptr, wptr to 0 */
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR, 0);
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR, 0);

	ih_doorbell_rtpr = RREG32_SOC15(OSSSYS, 0, mmIH_DOORBELL_RPTR);
	if (ih->use_doorbell) {
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr,
						 IH_DOORBELL_RPTR, OFFSET,
						 ih->doorbell_index);
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr,
						 IH_DOORBELL_RPTR, ENABLE, 1);
	} else {
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr,
						 IH_DOORBELL_RPTR, ENABLE, 0);
	}
	WREG32_SOC15(OSSSYS, 0, mmIH_DOORBELL_RPTR, ih_doorbell_rtpr);

	adev->nbio_funcs->ih_doorbell_range(adev, ih->use_doorbell,
					    ih->doorbell_index);

	tmp = RREG32_SOC15(OSSSYS, 0, mmIH_STORM_CLIENT_LIST_CNTL);
	tmp = REG_SET_FIELD(tmp, IH_STORM_CLIENT_LIST_CNTL,
			    CLIENT18_IS_STORM_CLIENT, 1);
	WREG32_SOC15(OSSSYS, 0, mmIH_STORM_CLIENT_LIST_CNTL, tmp);

	tmp = RREG32_SOC15(OSSSYS, 0, mmIH_INT_FLOOD_CNTL);
	tmp = REG_SET_FIELD(tmp, IH_INT_FLOOD_CNTL, FLOOD_CNTL_ENABLE, 1);
	WREG32_SOC15(OSSSYS, 0, mmIH_INT_FLOOD_CNTL, tmp);

	pci_set_master(adev->pdev);

	/* enable interrupts */
	navi10_ih_enable_interrupts(adev);

	return ret;
}