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
struct kv_power_info {TYPE_1__* graphics_level; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int EnabledForActivity; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static void kv_dpm_power_level_enable(struct amdgpu_device *adev,
				      u32 index, bool enable)
{
	struct kv_power_info *pi = kv_get_pi(adev);

	pi->graphics_level[index].EnabledForActivity = enable ? 1 : 0;
}