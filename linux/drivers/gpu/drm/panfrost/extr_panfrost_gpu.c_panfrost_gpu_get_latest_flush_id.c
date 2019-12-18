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
typedef  int /*<<< orphan*/  u32 ;
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPU_LATEST_FLUSH_ID ; 
 int /*<<< orphan*/  HW_FEATURE_FLUSH_REDUCTION ; 
 int /*<<< orphan*/  gpu_read (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ panfrost_has_hw_feature (struct panfrost_device*,int /*<<< orphan*/ ) ; 

u32 panfrost_gpu_get_latest_flush_id(struct panfrost_device *pfdev)
{
	if (panfrost_has_hw_feature(pfdev, HW_FEATURE_FLUSH_REDUCTION))
		return gpu_read(pfdev, GPU_LATEST_FLUSH_ID);
	return 0;
}