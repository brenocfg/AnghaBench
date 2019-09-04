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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int enabled; scalar_t__ rptr; } ;
struct TYPE_3__ {TYPE_2__ ih; } ;
struct amdgpu_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_INTR ; 
 int /*<<< orphan*/  IH_CNTL ; 
 int /*<<< orphan*/  IH_RB_CNTL ; 
 int /*<<< orphan*/  IH_RB_ENABLE ; 
 int /*<<< orphan*/  IH_RB_RPTR ; 
 int /*<<< orphan*/  IH_RB_WPTR ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_ih_disable_interrupts(struct amdgpu_device *adev)
{
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);
	u32 ih_cntl = RREG32(IH_CNTL);

	ih_rb_cntl &= ~IH_RB_ENABLE;
	ih_cntl &= ~ENABLE_INTR;
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	WREG32(IH_CNTL, ih_cntl);
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);
	adev->irq.ih.enabled = false;
	adev->irq.ih.rptr = 0;
}