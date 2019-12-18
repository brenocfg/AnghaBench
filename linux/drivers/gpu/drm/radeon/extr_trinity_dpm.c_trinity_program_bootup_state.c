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
typedef  int u32 ;
struct trinity_power_info {int /*<<< orphan*/  boot_pl; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_power_level_enable_disable (struct radeon_device*,int,int) ; 
 int /*<<< orphan*/  trinity_program_power_level (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trinity_program_bootup_state(struct radeon_device *rdev)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	u32 i;

	trinity_program_power_level(rdev, &pi->boot_pl, 0);
	trinity_power_level_enable_disable(rdev, 0, true);

	for (i = 1; i < 8; i++)
		trinity_power_level_enable_disable(rdev, i, false);
}