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
struct TYPE_3__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct TYPE_4__ {TYPE_1__ trap_irq; } ;
struct amdgpu_device {TYPE_2__ sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_SDMA_IRQ_LAST ; 
 int /*<<< orphan*/  si_dma_trap_irq_funcs ; 

__attribute__((used)) static void si_dma_set_irq_funcs(struct amdgpu_device *adev)
{
	adev->sdma.trap_irq.num_types = AMDGPU_SDMA_IRQ_LAST;
	adev->sdma.trap_irq.funcs = &si_dma_trap_irq_funcs;
}