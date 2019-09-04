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
struct sumo_power_info {int /*<<< orphan*/  psp; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_BSP_0 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void sumo_init_bsp(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);

	WREG32(CG_BSP_0, pi->psp);
}