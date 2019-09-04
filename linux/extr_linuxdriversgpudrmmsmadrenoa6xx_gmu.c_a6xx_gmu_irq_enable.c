#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct a6xx_gmu {int /*<<< orphan*/  hfi_irq; int /*<<< orphan*/  gmu_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  A6XX_GMU_IRQ_MASK ; 
 int /*<<< orphan*/  A6XX_HFI_IRQ_MASK ; 
 int /*<<< orphan*/  REG_A6XX_GMU_AO_HOST_INTERRUPT_CLR ; 
 int /*<<< orphan*/  REG_A6XX_GMU_AO_HOST_INTERRUPT_MASK ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GMU2HOST_INTR_CLR ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GMU2HOST_INTR_MASK ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a6xx_gmu_irq_enable(struct a6xx_gmu *gmu)
{
	gmu_write(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_CLR, ~0);
	gmu_write(gmu, REG_A6XX_GMU_GMU2HOST_INTR_CLR, ~0);

	gmu_write(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_MASK,
		~A6XX_GMU_IRQ_MASK);
	gmu_write(gmu, REG_A6XX_GMU_GMU2HOST_INTR_MASK,
		~A6XX_HFI_IRQ_MASK);

	enable_irq(gmu->gmu_irq);
	enable_irq(gmu->hfi_irq);
}