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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_5__ {int gpu_addr; int ring_size; int wptr_offs; } ;
struct TYPE_6__ {scalar_t__ msi_enabled; TYPE_2__ ih; } ;
struct TYPE_4__ {scalar_t__ gpu_addr; } ;
struct amdgpu_device {int dummy_page_addr; int /*<<< orphan*/  pdev; TYPE_3__ irq; TYPE_1__ wb; } ;

/* Variables and functions */
 int IH_CNTL__MC_VMID__SHIFT ; 
 int IH_CNTL__MC_WRREQ_CREDIT__SHIFT ; 
 int IH_CNTL__MC_WR_CLEAN_CNT__SHIFT ; 
 int IH_CNTL__RPTR_REARM_MASK ; 
 int IH_RB_CNTL__WPTR_OVERFLOW_CLEAR_MASK ; 
 int IH_RB_CNTL__WPTR_OVERFLOW_ENABLE_MASK ; 
 int IH_RB_CNTL__WPTR_WRITEBACK_ENABLE_MASK ; 
 int INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK ; 
 int INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cik_ih_disable_interrupts (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cik_ih_enable_interrupts (struct amdgpu_device*) ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mmIH_CNTL ; 
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
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int cik_ih_irq_init(struct amdgpu_device *adev)
{
	int rb_bufsz;
	u32 interrupt_cntl, ih_cntl, ih_rb_cntl;
	u64 wptr_off;

	/* disable irqs */
	cik_ih_disable_interrupts(adev);

	/* setup interrupt control */
	WREG32(mmINTERRUPT_CNTL2, adev->dummy_page_addr >> 8);
	interrupt_cntl = RREG32(mmINTERRUPT_CNTL);
	/* INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=0 - dummy read disabled with msi, enabled without msi
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=1 - dummy read controlled by IH_DUMMY_RD_EN
	 */
	interrupt_cntl &= ~INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK;
	/* INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK=1 if ring is in non-cacheable memory, e.g., vram */
	interrupt_cntl &= ~INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK;
	WREG32(mmINTERRUPT_CNTL, interrupt_cntl);

	WREG32(mmIH_RB_BASE, adev->irq.ih.gpu_addr >> 8);
	rb_bufsz = order_base_2(adev->irq.ih.ring_size / 4);

	ih_rb_cntl = (IH_RB_CNTL__WPTR_OVERFLOW_ENABLE_MASK |
		      IH_RB_CNTL__WPTR_OVERFLOW_CLEAR_MASK |
		      (rb_bufsz << 1));

	ih_rb_cntl |= IH_RB_CNTL__WPTR_WRITEBACK_ENABLE_MASK;

	/* set the writeback address whether it's enabled or not */
	wptr_off = adev->wb.gpu_addr + (adev->irq.ih.wptr_offs * 4);
	WREG32(mmIH_RB_WPTR_ADDR_LO, lower_32_bits(wptr_off));
	WREG32(mmIH_RB_WPTR_ADDR_HI, upper_32_bits(wptr_off) & 0xFF);

	WREG32(mmIH_RB_CNTL, ih_rb_cntl);

	/* set rptr, wptr to 0 */
	WREG32(mmIH_RB_RPTR, 0);
	WREG32(mmIH_RB_WPTR, 0);

	/* Default settings for IH_CNTL (disabled at first) */
	ih_cntl = (0x10 << IH_CNTL__MC_WRREQ_CREDIT__SHIFT) |
		(0x10 << IH_CNTL__MC_WR_CLEAN_CNT__SHIFT) |
		(0 << IH_CNTL__MC_VMID__SHIFT);
	/* IH_CNTL__RPTR_REARM_MASK only works if msi's are enabled */
	if (adev->irq.msi_enabled)
		ih_cntl |= IH_CNTL__RPTR_REARM_MASK;
	WREG32(mmIH_CNTL, ih_cntl);

	pci_set_master(adev->pdev);

	/* enable irqs */
	cik_ih_enable_interrupts(adev);

	return 0;
}