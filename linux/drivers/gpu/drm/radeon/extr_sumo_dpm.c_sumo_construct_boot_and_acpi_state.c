#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int allow_gnb_slow; scalar_t__ ss_divider_index; scalar_t__ ds_divider_index; int /*<<< orphan*/  vddc_index; int /*<<< orphan*/  sclk; } ;
struct TYPE_5__ {int num_levels; TYPE_3__* levels; } ;
struct TYPE_4__ {int /*<<< orphan*/  bootup_nb_voltage_index; int /*<<< orphan*/  bootup_sclk; } ;
struct sumo_power_info {TYPE_3__ boot_pl; TYPE_2__ current_ps; TYPE_3__ acpi_pl; TYPE_1__ sys_info; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void sumo_construct_boot_and_acpi_state(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);

	pi->boot_pl.sclk = pi->sys_info.bootup_sclk;
	pi->boot_pl.vddc_index = pi->sys_info.bootup_nb_voltage_index;
	pi->boot_pl.ds_divider_index = 0;
	pi->boot_pl.ss_divider_index = 0;
	pi->boot_pl.allow_gnb_slow = 1;
	pi->acpi_pl = pi->boot_pl;
	pi->current_ps.num_levels = 1;
	pi->current_ps.levels[0] = pi->boot_pl;
}