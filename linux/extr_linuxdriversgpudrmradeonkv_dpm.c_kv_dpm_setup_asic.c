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

/* Variables and functions */
 int /*<<< orphan*/  kv_init_powergate_state (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_init_sclk_t (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_take_smu_control (struct radeon_device*,int) ; 

void kv_dpm_setup_asic(struct radeon_device *rdev)
{
	sumo_take_smu_control(rdev, true);
	kv_init_powergate_state(rdev);
	kv_init_sclk_t(rdev);
}