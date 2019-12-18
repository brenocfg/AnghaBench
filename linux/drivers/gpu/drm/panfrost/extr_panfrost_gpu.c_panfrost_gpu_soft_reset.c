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
struct panfrost_device {int /*<<< orphan*/  dev; scalar_t__ iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPU_CMD ; 
 int GPU_CMD_SOFT_RESET ; 
 int /*<<< orphan*/  GPU_INT_CLEAR ; 
 int /*<<< orphan*/  GPU_INT_MASK ; 
 scalar_t__ GPU_INT_RAWSTAT ; 
 int GPU_IRQ_MASK_ALL ; 
 int GPU_IRQ_RESET_COMPLETED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int,int) ; 

int panfrost_gpu_soft_reset(struct panfrost_device *pfdev)
{
	int ret;
	u32 val;

	gpu_write(pfdev, GPU_INT_MASK, 0);
	gpu_write(pfdev, GPU_INT_CLEAR, GPU_IRQ_RESET_COMPLETED);
	gpu_write(pfdev, GPU_CMD, GPU_CMD_SOFT_RESET);

	ret = readl_relaxed_poll_timeout(pfdev->iomem + GPU_INT_RAWSTAT,
		val, val & GPU_IRQ_RESET_COMPLETED, 100, 10000);

	if (ret) {
		dev_err(pfdev->dev, "gpu soft reset timed out\n");
		return ret;
	}

	gpu_write(pfdev, GPU_INT_CLEAR, GPU_IRQ_MASK_ALL);
	gpu_write(pfdev, GPU_INT_MASK, GPU_IRQ_MASK_ALL);

	return 0;
}