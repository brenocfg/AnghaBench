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
 int /*<<< orphan*/  R600_POWER_LEVEL_MEDIUM ; 
 int /*<<< orphan*/  r600_power_level_set_enter_index (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv6xx_program_power_level_enter_state(struct radeon_device *rdev)
{
	r600_power_level_set_enter_index(rdev, R600_POWER_LEVEL_MEDIUM);
}