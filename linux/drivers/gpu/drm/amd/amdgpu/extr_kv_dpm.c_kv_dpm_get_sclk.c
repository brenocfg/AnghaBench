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
typedef  int /*<<< orphan*/  u32 ;
struct kv_ps {int num_levels; TYPE_1__* levels; } ;
struct kv_power_info {int /*<<< orphan*/  requested_rps; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sclk; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 struct kv_ps* kv_get_ps (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 kv_dpm_get_sclk(void *handle, bool low)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct kv_power_info *pi = kv_get_pi(adev);
	struct kv_ps *requested_state = kv_get_ps(&pi->requested_rps);

	if (low)
		return requested_state->levels[0].sclk;
	else
		return requested_state->levels[requested_state->num_levels - 1].sclk;
}