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

/* Variables and functions */
 int /*<<< orphan*/  A6XX_GMU_GMU2HOST_INTR_INFO_MSGQ ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GMU2HOST_INTR_MASK ; 
 int /*<<< orphan*/  REG_A6XX_GMU_HFI_CTRL_INIT ; 
 int /*<<< orphan*/  REG_A6XX_GMU_HFI_CTRL_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gmu_poll_timeout (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  gmu_rmw (struct a6xx_gmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int a6xx_gmu_hfi_start(struct a6xx_gmu *gmu)
{
	u32 val;
	int ret;

	gmu_rmw(gmu, REG_A6XX_GMU_GMU2HOST_INTR_MASK,
		A6XX_GMU_GMU2HOST_INTR_INFO_MSGQ, 0);

	gmu_write(gmu, REG_A6XX_GMU_HFI_CTRL_INIT, 1);

	ret = gmu_poll_timeout(gmu, REG_A6XX_GMU_HFI_CTRL_STATUS, val,
		val & 1, 100, 10000);
	if (ret)
		dev_err(gmu->dev, "Unable to start the HFI queues\n");

	return ret;
}