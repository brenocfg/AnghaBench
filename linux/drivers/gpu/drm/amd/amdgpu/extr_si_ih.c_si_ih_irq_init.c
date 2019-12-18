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
struct amdgpu_ih_ring {int gpu_addr; int ring_size; int /*<<< orphan*/  wptr_addr; } ;
struct TYPE_2__ {scalar_t__ msi_enabled; struct amdgpu_ih_ring ih; } ;
struct amdgpu_device {int /*<<< orphan*/  pdev; TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IH_CNTL ; 
 int IH_DUMMY_RD_OVERRIDE ; 
 int /*<<< orphan*/  IH_RB_BASE ; 
 int /*<<< orphan*/  IH_RB_CNTL ; 
 int /*<<< orphan*/  IH_RB_RPTR ; 
 int /*<<< orphan*/  IH_RB_WPTR ; 
 int /*<<< orphan*/  IH_RB_WPTR_ADDR_HI ; 
 int /*<<< orphan*/  IH_RB_WPTR_ADDR_LO ; 
 int IH_REQ_NONSNOOP_EN ; 
 int IH_WPTR_OVERFLOW_CLEAR ; 
 int IH_WPTR_OVERFLOW_ENABLE ; 
 int IH_WPTR_WRITEBACK_ENABLE ; 
 int /*<<< orphan*/  INTERRUPT_CNTL ; 
 int /*<<< orphan*/  INTERRUPT_CNTL2 ; 
 int MC_VMID (int /*<<< orphan*/ ) ; 
 int MC_WRREQ_CREDIT (int) ; 
 int MC_WR_CLEAN_CNT (int) ; 
 int RPTR_REARM ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int order_base_2 (int) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_ih_disable_interrupts (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_ih_enable_interrupts (struct amdgpu_device*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_ih_irq_init(struct amdgpu_device *adev)
{
	struct amdgpu_ih_ring *ih = &adev->irq.ih;
	int rb_bufsz;
	u32 interrupt_cntl, ih_cntl, ih_rb_cntl;

	si_ih_disable_interrupts(adev);
	WREG32(INTERRUPT_CNTL2, adev->irq.ih.gpu_addr >> 8);
	interrupt_cntl = RREG32(INTERRUPT_CNTL);
	interrupt_cntl &= ~IH_DUMMY_RD_OVERRIDE;
	interrupt_cntl &= ~IH_REQ_NONSNOOP_EN;
	WREG32(INTERRUPT_CNTL, interrupt_cntl);

	WREG32(IH_RB_BASE, adev->irq.ih.gpu_addr >> 8);
	rb_bufsz = order_base_2(adev->irq.ih.ring_size / 4);

	ih_rb_cntl = IH_WPTR_OVERFLOW_ENABLE |
		     IH_WPTR_OVERFLOW_CLEAR |
		     (rb_bufsz << 1) |
		     IH_WPTR_WRITEBACK_ENABLE;

	WREG32(IH_RB_WPTR_ADDR_LO, lower_32_bits(ih->wptr_addr));
	WREG32(IH_RB_WPTR_ADDR_HI, upper_32_bits(ih->wptr_addr) & 0xFF);
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);

	ih_cntl = MC_WRREQ_CREDIT(0x10) | MC_WR_CLEAN_CNT(0x10) | MC_VMID(0);
	if (adev->irq.msi_enabled)
		ih_cntl |= RPTR_REARM;
	WREG32(IH_CNTL, ih_cntl);

	pci_set_master(adev->pdev);
	si_ih_enable_interrupts(adev);

	return 0;
}