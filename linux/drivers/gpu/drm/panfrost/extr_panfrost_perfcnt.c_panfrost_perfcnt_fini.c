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
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPU_PERFCNT_CFG ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG_MODE_OFF ; 
 int /*<<< orphan*/  GPU_PRFCNT_JM_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_MMU_L2_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_SHADER_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_TILER_EN ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void panfrost_perfcnt_fini(struct panfrost_device *pfdev)
{
	/* Disable everything before leaving. */
	gpu_write(pfdev, GPU_PERFCNT_CFG,
		  GPU_PERFCNT_CFG_MODE(GPU_PERFCNT_CFG_MODE_OFF));
	gpu_write(pfdev, GPU_PRFCNT_JM_EN, 0);
	gpu_write(pfdev, GPU_PRFCNT_SHADER_EN, 0);
	gpu_write(pfdev, GPU_PRFCNT_MMU_L2_EN, 0);
	gpu_write(pfdev, GPU_PRFCNT_TILER_EN, 0);
}