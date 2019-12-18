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
typedef  scalar_t__ u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r600_engine_clock_entry_enable (struct radeon_device*,scalar_t__,int) ; 

__attribute__((used)) static void rv6xx_invalidate_intermediate_steps_range(struct radeon_device *rdev,
						      u32 start_index, u32 end_index)
{
	u32 step_index;

	for (step_index = start_index + 1; step_index < end_index; step_index++)
		r600_engine_clock_entry_enable(rdev, step_index, false);
}