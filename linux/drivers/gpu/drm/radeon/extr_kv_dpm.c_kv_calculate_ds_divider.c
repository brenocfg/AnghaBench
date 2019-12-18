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
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct kv_power_info {scalar_t__ lowest_valid; scalar_t__ highest_valid; TYPE_1__* graphics_level; } ;
struct TYPE_2__ {int /*<<< orphan*/  SclkFrequency; int /*<<< orphan*/  DeepSleepDivId; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_get_sleep_divider_id_from_clock (struct radeon_device*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int kv_calculate_ds_divider(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	u32 sclk_in_sr = 10000; /* ??? */
	u32 i;

	if (pi->lowest_valid > pi->highest_valid)
		return -EINVAL;

	for (i = pi->lowest_valid; i <= pi->highest_valid; i++) {
		pi->graphics_level[i].DeepSleepDivId =
			kv_get_sleep_divider_id_from_clock(rdev,
							   be32_to_cpu(pi->graphics_level[i].SclkFrequency),
							   sclk_in_sr);
	}
	return 0;
}