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
 int /*<<< orphan*/  panfrost_clk_fini (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_gpu_fini (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_job_fini (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_mmu_fini (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_perfcnt_fini (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_regulator_fini (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_reset_fini (struct panfrost_device*) ; 

void panfrost_device_fini(struct panfrost_device *pfdev)
{
	panfrost_perfcnt_fini(pfdev);
	panfrost_job_fini(pfdev);
	panfrost_mmu_fini(pfdev);
	panfrost_gpu_fini(pfdev);
	panfrost_reset_fini(pfdev);
	panfrost_regulator_fini(pfdev);
	panfrost_clk_fini(pfdev);
}