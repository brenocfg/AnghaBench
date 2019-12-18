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
struct msm_gpu {int dummy; } ;
struct adreno_gpu {int dummy; } ;

/* Variables and functions */
 unsigned int A4XX_RBBM_POWER_CNTL_IP_SP_TP_PWR_ON ; 
 int /*<<< orphan*/  REG_A4XX_RBBM_POWER_CNTL_IP ; 
 int /*<<< orphan*/  REG_A4XX_RBBM_POWER_STATUS ; 
 scalar_t__ adreno_is_a430 (struct adreno_gpu*) ; 
 unsigned int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int msm_gpu_pm_resume (struct msm_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int a4xx_pm_resume(struct msm_gpu *gpu) {
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	int ret;

	ret = msm_gpu_pm_resume(gpu);
	if (ret)
		return ret;

	if (adreno_is_a430(adreno_gpu)) {
		unsigned int reg;
		/* Set the default register values; set SW_COLLAPSE to 0 */
		gpu_write(gpu, REG_A4XX_RBBM_POWER_CNTL_IP, 0x778000);
		do {
			udelay(5);
			reg = gpu_read(gpu, REG_A4XX_RBBM_POWER_STATUS);
		} while (!(reg & A4XX_RBBM_POWER_CNTL_IP_SP_TP_PWR_ON));
	}
	return 0;
}