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
struct radeon_device {int dummy; } ;
struct kv_power_info {scalar_t__ bapm_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int kv_smc_bapm_enable (struct radeon_device*,int) ; 

void kv_dpm_enable_bapm(struct radeon_device *rdev, bool enable)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	int ret;

	if (pi->bapm_enable) {
		ret = kv_smc_bapm_enable(rdev, enable);
		if (ret)
			DRM_ERROR("kv_smc_bapm_enable failed\n");
	}
}