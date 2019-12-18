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
typedef  int u64 ;
typedef  int u32 ;
struct panfrost_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPU_FAULT_ADDRESS_HI ; 
 int /*<<< orphan*/  GPU_FAULT_ADDRESS_LO ; 
 int /*<<< orphan*/  GPU_FAULT_STATUS ; 
 int /*<<< orphan*/  GPU_INT_CLEAR ; 
 int /*<<< orphan*/  GPU_INT_MASK ; 
 int /*<<< orphan*/  GPU_INT_STAT ; 
 int GPU_IRQ_CLEAN_CACHES_COMPLETED ; 
 int GPU_IRQ_MASK_ERROR ; 
 int GPU_IRQ_MULTIPLE_FAULT ; 
 int GPU_IRQ_PERFCNT_SAMPLE_COMPLETED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int gpu_read (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panfrost_exception_name (struct panfrost_device*,int) ; 
 int /*<<< orphan*/  panfrost_perfcnt_clean_cache_done (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_perfcnt_sample_done (struct panfrost_device*) ; 

__attribute__((used)) static irqreturn_t panfrost_gpu_irq_handler(int irq, void *data)
{
	struct panfrost_device *pfdev = data;
	u32 state = gpu_read(pfdev, GPU_INT_STAT);
	u32 fault_status = gpu_read(pfdev, GPU_FAULT_STATUS);

	if (!state)
		return IRQ_NONE;

	if (state & GPU_IRQ_MASK_ERROR) {
		u64 address = (u64) gpu_read(pfdev, GPU_FAULT_ADDRESS_HI) << 32;
		address |= gpu_read(pfdev, GPU_FAULT_ADDRESS_LO);

		dev_warn(pfdev->dev, "GPU Fault 0x%08x (%s) at 0x%016llx\n",
			 fault_status & 0xFF, panfrost_exception_name(pfdev, fault_status),
			 address);

		if (state & GPU_IRQ_MULTIPLE_FAULT)
			dev_warn(pfdev->dev, "There were multiple GPU faults - some have not been reported\n");

		gpu_write(pfdev, GPU_INT_MASK, 0);
	}

	if (state & GPU_IRQ_PERFCNT_SAMPLE_COMPLETED)
		panfrost_perfcnt_sample_done(pfdev);

	if (state & GPU_IRQ_CLEAN_CACHES_COMPLETED)
		panfrost_perfcnt_clean_cache_done(pfdev);

	gpu_write(pfdev, GPU_INT_CLEAR, state);

	return IRQ_HANDLED;
}