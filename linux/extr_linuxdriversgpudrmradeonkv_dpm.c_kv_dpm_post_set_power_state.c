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
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct kv_power_info {struct radeon_ps requested_rps; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_update_current_ps (struct radeon_device*,struct radeon_ps*) ; 

void kv_dpm_post_set_power_state(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	struct radeon_ps *new_ps = &pi->requested_rps;

	kv_update_current_ps(rdev, new_ps);
}