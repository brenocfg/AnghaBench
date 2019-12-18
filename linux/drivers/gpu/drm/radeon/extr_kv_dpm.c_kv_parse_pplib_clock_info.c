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
struct TYPE_2__ {int ucEngineClockHigh; int /*<<< orphan*/  vddcIndex; int /*<<< orphan*/  usEngineClockLow; } ;
union pplib_clock_info {TYPE_1__ sumo; } ;
typedef  int u32 ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct kv_ps {int num_levels; struct kv_pl* levels; } ;
struct kv_power_info {scalar_t__ caps_sclk_ds; } ;
struct kv_pl {int sclk; int ds_divider_index; int ss_divider_index; int /*<<< orphan*/  vddc_index; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 struct kv_ps* kv_get_ps (struct radeon_ps*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kv_parse_pplib_clock_info(struct radeon_device *rdev,
				      struct radeon_ps *rps, int index,
					union pplib_clock_info *clock_info)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	struct kv_ps *ps = kv_get_ps(rps);
	struct kv_pl *pl = &ps->levels[index];
	u32 sclk;

	sclk = le16_to_cpu(clock_info->sumo.usEngineClockLow);
	sclk |= clock_info->sumo.ucEngineClockHigh << 16;
	pl->sclk = sclk;
	pl->vddc_index = clock_info->sumo.vddcIndex;

	ps->num_levels = index + 1;

	if (pi->caps_sclk_ds) {
		pl->ds_divider_index = 5;
		pl->ss_divider_index = 5;
	}
}