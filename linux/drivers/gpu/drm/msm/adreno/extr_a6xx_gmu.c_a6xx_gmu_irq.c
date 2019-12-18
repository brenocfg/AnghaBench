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
typedef  int u32 ;
struct a6xx_gmu {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int A6XX_GMU_AO_HOST_INTERRUPT_STATUS_FENCE_ERR ; 
 int A6XX_GMU_AO_HOST_INTERRUPT_STATUS_HOST_AHB_BUS_ERROR ; 
 int A6XX_GMU_AO_HOST_INTERRUPT_STATUS_WDOG_BITE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_A6XX_GMU_AHB_FENCE_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_GMU_AO_HOST_INTERRUPT_CLR ; 
 int /*<<< orphan*/  REG_A6XX_GMU_AO_HOST_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  a6xx_gmu_fault (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t a6xx_gmu_irq(int irq, void *data)
{
	struct a6xx_gmu *gmu = data;
	u32 status;

	status = gmu_read(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_STATUS);
	gmu_write(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_CLR, status);

	if (status & A6XX_GMU_AO_HOST_INTERRUPT_STATUS_WDOG_BITE) {
		dev_err_ratelimited(gmu->dev, "GMU watchdog expired\n");

		a6xx_gmu_fault(gmu);
	}

	if (status &  A6XX_GMU_AO_HOST_INTERRUPT_STATUS_HOST_AHB_BUS_ERROR)
		dev_err_ratelimited(gmu->dev, "GMU AHB bus error\n");

	if (status & A6XX_GMU_AO_HOST_INTERRUPT_STATUS_FENCE_ERR)
		dev_err_ratelimited(gmu->dev, "GMU fence error: 0x%x\n",
			gmu_read(gmu, REG_A6XX_GMU_AHB_FENCE_STATUS));

	return IRQ_HANDLED;
}