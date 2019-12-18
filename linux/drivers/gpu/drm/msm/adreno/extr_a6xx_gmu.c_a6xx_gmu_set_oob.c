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
typedef  enum a6xx_gmu_oob_state { ____Placeholder_a6xx_gmu_oob_state } a6xx_gmu_oob_state ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  GMU_OOB_BOOT_SLUMBER 130 
 int GMU_OOB_BOOT_SLUMBER_ACK ; 
 int GMU_OOB_BOOT_SLUMBER_REQUEST ; 
 int GMU_OOB_DCVS_ACK ; 
 int GMU_OOB_DCVS_REQUEST ; 
#define  GMU_OOB_DCVS_SET 129 
#define  GMU_OOB_GPU_SET 128 
 int GMU_OOB_GPU_SET_ACK ; 
 int GMU_OOB_GPU_SET_REQUEST ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GMU2HOST_INTR_CLR ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GMU2HOST_INTR_INFO ; 
 int /*<<< orphan*/  REG_A6XX_GMU_HOST2GMU_INTR_SET ; 
 int gmu_poll_timeout (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

int a6xx_gmu_set_oob(struct a6xx_gmu *gmu, enum a6xx_gmu_oob_state state)
{
	int ret;
	u32 val;
	int request, ack;
	const char *name;

	switch (state) {
	case GMU_OOB_GPU_SET:
		request = GMU_OOB_GPU_SET_REQUEST;
		ack = GMU_OOB_GPU_SET_ACK;
		name = "GPU_SET";
		break;
	case GMU_OOB_BOOT_SLUMBER:
		request = GMU_OOB_BOOT_SLUMBER_REQUEST;
		ack = GMU_OOB_BOOT_SLUMBER_ACK;
		name = "BOOT_SLUMBER";
		break;
	case GMU_OOB_DCVS_SET:
		request = GMU_OOB_DCVS_REQUEST;
		ack = GMU_OOB_DCVS_ACK;
		name = "GPU_DCVS";
		break;
	default:
		return -EINVAL;
	}

	/* Trigger the equested OOB operation */
	gmu_write(gmu, REG_A6XX_GMU_HOST2GMU_INTR_SET, 1 << request);

	/* Wait for the acknowledge interrupt */
	ret = gmu_poll_timeout(gmu, REG_A6XX_GMU_GMU2HOST_INTR_INFO, val,
		val & (1 << ack), 100, 10000);

	if (ret)
		DRM_DEV_ERROR(gmu->dev,
			"Timeout waiting for GMU OOB set %s: 0x%x\n",
				name,
				gmu_read(gmu, REG_A6XX_GMU_GMU2HOST_INTR_INFO));

	/* Clear the acknowledge interrupt */
	gmu_write(gmu, REG_A6XX_GMU_GMU2HOST_INTR_CLR, 1 << ack);

	return ret;
}