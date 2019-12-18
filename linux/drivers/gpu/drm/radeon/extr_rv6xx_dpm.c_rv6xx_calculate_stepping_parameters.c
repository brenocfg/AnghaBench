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
struct rv6xx_ps {int dummy; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rv6xx_calculate_ap (struct radeon_device*,struct rv6xx_ps*) ; 
 int /*<<< orphan*/  rv6xx_calculate_engine_speed_stepping_parameters (struct radeon_device*,struct rv6xx_ps*) ; 
 int /*<<< orphan*/  rv6xx_calculate_memory_clock_stepping_parameters (struct radeon_device*,struct rv6xx_ps*) ; 
 int /*<<< orphan*/  rv6xx_calculate_voltage_stepping_parameters (struct radeon_device*,struct rv6xx_ps*) ; 
 struct rv6xx_ps* rv6xx_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void rv6xx_calculate_stepping_parameters(struct radeon_device *rdev,
						struct radeon_ps *new_ps)
{
	struct rv6xx_ps *new_state = rv6xx_get_ps(new_ps);

	rv6xx_calculate_engine_speed_stepping_parameters(rdev, new_state);
	rv6xx_calculate_memory_clock_stepping_parameters(rdev, new_state);
	rv6xx_calculate_voltage_stepping_parameters(rdev, new_state);
	rv6xx_calculate_ap(rdev, new_state);
}