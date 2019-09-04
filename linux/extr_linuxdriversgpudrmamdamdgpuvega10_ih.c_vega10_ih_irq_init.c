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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_7__ {int rb_dma_addr; int gpu_addr; int ring_size; int wptr_offs; int doorbell_index; scalar_t__ use_doorbell; scalar_t__ use_bus_addr; } ;
struct TYPE_8__ {TYPE_3__ ih; scalar_t__ msi_enabled; } ;
struct TYPE_5__ {int gpu_addr; } ;
struct amdgpu_device {int /*<<< orphan*/  pdev; TYPE_4__ irq; TYPE_2__* nbio_funcs; TYPE_1__ wb; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ih_doorbell_range ) (struct amdgpu_device*,scalar_t__,int) ;int /*<<< orphan*/  (* ih_control ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT18_IS_STORM_CLIENT ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  FLOOD_CNTL_ENABLE ; 
 int /*<<< orphan*/  IH_DOORBELL_RPTR ; 
 int /*<<< orphan*/  IH_INT_FLOOD_CNTL ; 
 int /*<<< orphan*/  IH_RB_CNTL ; 
 int /*<<< orphan*/  IH_STORM_CLIENT_LIST_CNTL ; 
 int /*<<< orphan*/  MC_RO ; 
 int /*<<< orphan*/  MC_SNOOP ; 
 int /*<<< orphan*/  MC_SPACE ; 
 int /*<<< orphan*/  MC_VMID ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  OSSSYS ; 
 int /*<<< orphan*/  RB_SIZE ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RPTR_REARM ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPTR_OVERFLOW_CLEAR ; 
 int /*<<< orphan*/  WPTR_OVERFLOW_ENABLE ; 
 int /*<<< orphan*/  WPTR_WRITEBACK_ENABLE ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int) ; 
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
 int order_base_2 (int) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*,scalar_t__,int) ; 
 int upper_32_bits (int) ; 
 int /*<<< orphan*/  vega10_ih_disable_interrupts (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vega10_ih_enable_interrupts (struct amdgpu_device*) ; 

__attribute__((used)) static int vega10_ih_irq_init(struct amdgpu_device *adev)
{
	int ret = 0;
	int rb_bufsz;
	u32 ih_rb_cntl, ih_doorbell_rtpr;
	u32 tmp;
	u64 wptr_off;

	/* disable irqs */
	vega10_ih_disable_interrupts(adev);

	adev->nbio_funcs->ih_control(adev);

	ih_rb_cntl = RREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL);
	/* Ring Buffer base. [39:8] of 40-bit address of the beginning of the ring buffer*/
	if (adev->irq.ih.use_bus_addr) {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE, adev->irq.ih.rb_dma_addr >> 8);
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE_HI, ((u64)adev->irq.ih.rb_dma_addr >> 40) & 0xff);
		ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_SPACE, 1);
	} else {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE, adev->irq.ih.gpu_addr >> 8);
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_BASE_HI, (adev->irq.ih.gpu_addr >> 40) & 0xff);
		ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_SPACE, 4);
	}
	rb_bufsz = order_base_2(adev->irq.ih.ring_size / 4);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, WPTR_OVERFLOW_CLEAR, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, WPTR_OVERFLOW_ENABLE, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RB_SIZE, rb_bufsz);
	/* Ring Buffer write pointer writeback. If enabled, IH_RB_WPTR register value is written to memory */
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, WPTR_WRITEBACK_ENABLE, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_SNOOP, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_RO, 0);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_VMID, 0);

	if (adev->irq.msi_enabled)
		ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RPTR_REARM, 1);

	WREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL, ih_rb_cntl);

	/* set the writeback address whether it's enabled or not */
	if (adev->irq.ih.use_bus_addr)
		wptr_off = adev->irq.ih.rb_dma_addr + (adev->irq.ih.wptr_offs * 4);
	else
		wptr_off = adev->wb.gpu_addr + (adev->irq.ih.wptr_offs * 4);
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR_ADDR_LO, lower_32_bits(wptr_off));
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR_ADDR_HI, upper_32_bits(wptr_off) & 0xFFFF);

	/* set rptr, wptr to 0 */
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR, 0);
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_WPTR, 0);

	ih_doorbell_rtpr = RREG32_SOC15(OSSSYS, 0, mmIH_DOORBELL_RPTR);
	if (adev->irq.ih.use_doorbell) {
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr, IH_DOORBELL_RPTR,
						 OFFSET, adev->irq.ih.doorbell_index);
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr, IH_DOORBELL_RPTR,
						 ENABLE, 1);
	} else {
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr, IH_DOORBELL_RPTR,
						 ENABLE, 0);
	}
	WREG32_SOC15(OSSSYS, 0, mmIH_DOORBELL_RPTR, ih_doorbell_rtpr);
	adev->nbio_funcs->ih_doorbell_range(adev, adev->irq.ih.use_doorbell,
					    adev->irq.ih.doorbell_index);

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