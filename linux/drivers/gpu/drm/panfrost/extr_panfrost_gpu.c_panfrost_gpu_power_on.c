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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ l2_present; scalar_t__ stack_present; scalar_t__ shader_present; scalar_t__ tiler_present; } ;
struct panfrost_device {int /*<<< orphan*/  dev; TYPE_1__ features; scalar_t__ iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2_PWRON_LO ; 
 scalar_t__ L2_READY_LO ; 
 int /*<<< orphan*/  SHADER_PWRON_LO ; 
 scalar_t__ SHADER_READY_LO ; 
 int /*<<< orphan*/  STACK_PWRON_LO ; 
 scalar_t__ STACK_READY_LO ; 
 int /*<<< orphan*/  TILER_PWRON_LO ; 
 scalar_t__ TILER_READY_LO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int readl_relaxed_poll_timeout (scalar_t__,scalar_t__,int,int,int) ; 

void panfrost_gpu_power_on(struct panfrost_device *pfdev)
{
	int ret;
	u32 val;

	/* Just turn on everything for now */
	gpu_write(pfdev, L2_PWRON_LO, pfdev->features.l2_present);
	ret = readl_relaxed_poll_timeout(pfdev->iomem + L2_READY_LO,
		val, val == pfdev->features.l2_present, 100, 1000);

	gpu_write(pfdev, STACK_PWRON_LO, pfdev->features.stack_present);
	ret |= readl_relaxed_poll_timeout(pfdev->iomem + STACK_READY_LO,
		val, val == pfdev->features.stack_present, 100, 1000);

	gpu_write(pfdev, SHADER_PWRON_LO, pfdev->features.shader_present);
	ret |= readl_relaxed_poll_timeout(pfdev->iomem + SHADER_READY_LO,
		val, val == pfdev->features.shader_present, 100, 1000);

	gpu_write(pfdev, TILER_PWRON_LO, pfdev->features.tiler_present);
	ret |= readl_relaxed_poll_timeout(pfdev->iomem + TILER_READY_LO,
		val, val == pfdev->features.tiler_present, 100, 1000);

	if (ret)
		dev_err(pfdev->dev, "error powering up gpu");
}