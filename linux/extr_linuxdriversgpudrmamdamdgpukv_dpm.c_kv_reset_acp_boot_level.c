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
struct kv_power_info {int acp_boot_level; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static void kv_reset_acp_boot_level(struct amdgpu_device *adev)
{
	struct kv_power_info *pi = kv_get_pi(adev);

	pi->acp_boot_level = 0xff;
}