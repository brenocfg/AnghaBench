#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int dummy; } ;
struct TYPE_4__ {int allow_gnb_slow; scalar_t__ vce_wm; scalar_t__ display_wm; scalar_t__ force_nbp_state; scalar_t__ ss_divider_index; scalar_t__ ds_divider_index; int /*<<< orphan*/  vddc_index; int /*<<< orphan*/  sclk; } ;
struct TYPE_3__ {int /*<<< orphan*/  bootup_nb_voltage_index; int /*<<< orphan*/  bootup_sclk; } ;
struct kv_power_info {TYPE_2__ boot_pl; TYPE_1__ sys_info; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void kv_construct_boot_state(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);

	pi->boot_pl.sclk = pi->sys_info.bootup_sclk;
	pi->boot_pl.vddc_index = pi->sys_info.bootup_nb_voltage_index;
	pi->boot_pl.ds_divider_index = 0;
	pi->boot_pl.ss_divider_index = 0;
	pi->boot_pl.allow_gnb_slow = 1;
	pi->boot_pl.force_nbp_state = 0;
	pi->boot_pl.display_wm = 0;
	pi->boot_pl.vce_wm = 0;
}