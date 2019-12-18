#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct amdgpu_ih_ring {int gpu_addr; int ring_size; int doorbell_index; scalar_t__ use_doorbell; int /*<<< orphan*/  wptr_addr; } ;
struct TYPE_2__ {struct amdgpu_ih_ring ih; scalar_t__ msi_enabled; } ;
struct amdgpu_device {int dummy_page_addr; int /*<<< orphan*/  pdev; TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  IH_DOORBELL_RPTR ; 
 int /*<<< orphan*/  IH_DUMMY_RD_OVERRIDE ; 
 int /*<<< orphan*/  IH_RB_CNTL ; 
 int /*<<< orphan*/  IH_REQ_NONSNOOP_EN ; 
 int /*<<< orphan*/  INTERRUPT_CNTL ; 
 int /*<<< orphan*/  MC_VMID ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  RB_SIZE ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RPTR_REARM ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPTR_OVERFLOW_CLEAR ; 
 int /*<<< orphan*/  WPTR_WRITEBACK_ENABLE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmIH_DOORBELL_RPTR ; 
 int /*<<< orphan*/  mmIH_RB_BASE ; 
 int /*<<< orphan*/  mmIH_RB_CNTL ; 
 int /*<<< orphan*/  mmIH_RB_RPTR ; 
 int /*<<< orphan*/  mmIH_RB_WPTR ; 
 int /*<<< orphan*/  mmIH_RB_WPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmIH_RB_WPTR_ADDR_LO ; 
 int /*<<< orphan*/  mmINTERRUPT_CNTL ; 
 int /*<<< orphan*/  mmINTERRUPT_CNTL2 ; 
 int order_base_2 (int) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tonga_ih_disable_interrupts (struct amdgpu_device*) ; 
 int /*<<< orphan*/  tonga_ih_enable_interrupts (struct amdgpu_device*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tonga_ih_irq_init(struct amdgpu_device *adev)
{
	u32 interrupt_cntl, ih_rb_cntl, ih_doorbell_rtpr;
	struct amdgpu_ih_ring *ih = &adev->irq.ih;
	int rb_bufsz;

	/* disable irqs */
	tonga_ih_disable_interrupts(adev);

	/* setup interrupt control */
	WREG32(mmINTERRUPT_CNTL2, adev->dummy_page_addr >> 8);
	interrupt_cntl = RREG32(mmINTERRUPT_CNTL);
	/* INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=0 - dummy read disabled with msi, enabled without msi
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=1 - dummy read controlled by IH_DUMMY_RD_EN
	 */
	interrupt_cntl = REG_SET_FIELD(interrupt_cntl, INTERRUPT_CNTL, IH_DUMMY_RD_OVERRIDE, 0);
	/* INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK=1 if ring is in non-cacheable memory, e.g., vram */
	interrupt_cntl = REG_SET_FIELD(interrupt_cntl, INTERRUPT_CNTL, IH_REQ_NONSNOOP_EN, 0);
	WREG32(mmINTERRUPT_CNTL, interrupt_cntl);

	/* Ring Buffer base. [39:8] of 40-bit address of the beginning of the ring buffer*/
	WREG32(mmIH_RB_BASE, ih->gpu_addr >> 8);

	rb_bufsz = order_base_2(adev->irq.ih.ring_size / 4);
	ih_rb_cntl = REG_SET_FIELD(0, IH_RB_CNTL, WPTR_OVERFLOW_CLEAR, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RB_SIZE, rb_bufsz);
	/* Ring Buffer write pointer writeback. If enabled, IH_RB_WPTR register value is written to memory */
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, WPTR_WRITEBACK_ENABLE, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_VMID, 0);

	if (adev->irq.msi_enabled)
		ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RPTR_REARM, 1);

	WREG32(mmIH_RB_CNTL, ih_rb_cntl);

	/* set the writeback address whether it's enabled or not */
	WREG32(mmIH_RB_WPTR_ADDR_LO, lower_32_bits(ih->wptr_addr));
	WREG32(mmIH_RB_WPTR_ADDR_HI, upper_32_bits(ih->wptr_addr) & 0xFF);

	/* set rptr, wptr to 0 */
	WREG32(mmIH_RB_RPTR, 0);
	WREG32(mmIH_RB_WPTR, 0);

	ih_doorbell_rtpr = RREG32(mmIH_DOORBELL_RPTR);
	if (adev->irq.ih.use_doorbell) {
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr, IH_DOORBELL_RPTR,
						 OFFSET, adev->irq.ih.doorbell_index);
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr, IH_DOORBELL_RPTR,
						 ENABLE, 1);
	} else {
		ih_doorbell_rtpr = REG_SET_FIELD(ih_doorbell_rtpr, IH_DOORBELL_RPTR,
						 ENABLE, 0);
	}
	WREG32(mmIH_DOORBELL_RPTR, ih_doorbell_rtpr);

	pci_set_master(adev->pdev);

	/* enable interrupts */
	tonga_ih_enable_interrupts(adev);

	return 0;
}