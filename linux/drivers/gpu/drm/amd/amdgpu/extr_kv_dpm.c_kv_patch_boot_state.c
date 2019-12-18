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
struct kv_ps {int num_levels; int /*<<< orphan*/ * levels; } ;
struct kv_power_info {int /*<<< orphan*/  boot_pl; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static void kv_patch_boot_state(struct amdgpu_device *adev,
				struct kv_ps *ps)
{
	struct kv_power_info *pi = kv_get_pi(adev);

	ps->num_levels = 1;
	ps->levels[0] = pi->boot_pl;
}