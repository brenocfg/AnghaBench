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
struct msm_gpu {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_RBCCU_POWER_CNTL ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_RBCCU_PWR_CLK_STATUS ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_SP_POWER_CNTL ; 
 int /*<<< orphan*/  REG_A5XX_GPMU_SP_PWR_CLK_STATUS ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int msm_gpu_pm_resume (struct msm_gpu*) ; 
 int spin_usecs (struct msm_gpu*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int a5xx_pm_resume(struct msm_gpu *gpu)
{
	int ret;

	/* Turn on the core power */
	ret = msm_gpu_pm_resume(gpu);
	if (ret)
		return ret;

	/* Turn the RBCCU domain first to limit the chances of voltage droop */
	gpu_write(gpu, REG_A5XX_GPMU_RBCCU_POWER_CNTL, 0x778000);

	/* Wait 3 usecs before polling */
	udelay(3);

	ret = spin_usecs(gpu, 20, REG_A5XX_GPMU_RBCCU_PWR_CLK_STATUS,
		(1 << 20), (1 << 20));
	if (ret) {
		DRM_ERROR("%s: timeout waiting for RBCCU GDSC enable: %X\n",
			gpu->name,
			gpu_read(gpu, REG_A5XX_GPMU_RBCCU_PWR_CLK_STATUS));
		return ret;
	}

	/* Turn on the SP domain */
	gpu_write(gpu, REG_A5XX_GPMU_SP_POWER_CNTL, 0x778000);
	ret = spin_usecs(gpu, 20, REG_A5XX_GPMU_SP_PWR_CLK_STATUS,
		(1 << 20), (1 << 20));
	if (ret)
		DRM_ERROR("%s: timeout waiting for SP GDSC enable\n",
			gpu->name);

	return ret;
}