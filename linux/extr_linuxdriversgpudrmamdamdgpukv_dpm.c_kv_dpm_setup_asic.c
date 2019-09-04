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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kv_init_powergate_state (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_init_sclk_t (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sumo_take_smu_control (struct amdgpu_device*,int) ; 

__attribute__((used)) static void kv_dpm_setup_asic(struct amdgpu_device *adev)
{
	sumo_take_smu_control(adev, true);
	kv_init_powergate_state(adev);
	kv_init_sclk_t(adev);
}