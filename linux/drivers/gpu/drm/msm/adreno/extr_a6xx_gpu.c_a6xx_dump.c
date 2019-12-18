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
struct msm_gpu {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_INFO (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_STATUS ; 
 int /*<<< orphan*/  adreno_dump (struct msm_gpu*) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a6xx_dump(struct msm_gpu *gpu)
{
	DRM_DEV_INFO(&gpu->pdev->dev, "status:   %08x\n",
			gpu_read(gpu, REG_A6XX_RBBM_STATUS));
	adreno_dump(gpu);
}