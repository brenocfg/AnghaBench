#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ supported; } ;
struct evergreen_power_info {int /*<<< orphan*/  bootup_arb_registers; TYPE_1__ ulv; } ;

/* Variables and functions */
 int /*<<< orphan*/  btc_set_arb0_registers (struct radeon_device*,int /*<<< orphan*/ *) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void btc_set_boot_state_timing(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);

	if (eg_pi->ulv.supported)
		btc_set_arb0_registers(rdev, &eg_pi->bootup_arb_registers);
}