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
 int /*<<< orphan*/  trinity_power_level_enable_disable (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void trinity_enable_power_level_0(struct radeon_device *rdev)
{
	trinity_power_level_enable_disable(rdev, 0, true);
}