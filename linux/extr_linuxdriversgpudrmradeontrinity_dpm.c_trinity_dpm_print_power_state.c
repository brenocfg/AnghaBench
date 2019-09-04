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
struct trinity_ps {int num_levels; struct trinity_pl* levels; } ;
struct trinity_pl {int /*<<< orphan*/  vddc_index; int /*<<< orphan*/  sclk; } ;
struct radeon_ps {int /*<<< orphan*/  dclk; int /*<<< orphan*/  vclk; int /*<<< orphan*/  caps; int /*<<< orphan*/  class2; int /*<<< orphan*/  class; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  r600_dpm_print_cap_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_dpm_print_class_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_dpm_print_ps_status (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_convert_voltage_index_to_value (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct trinity_ps* trinity_get_ps (struct radeon_ps*) ; 

void trinity_dpm_print_power_state(struct radeon_device *rdev,
				   struct radeon_ps *rps)
{
	int i;
	struct trinity_ps *ps = trinity_get_ps(rps);

	r600_dpm_print_class_info(rps->class, rps->class2);
	r600_dpm_print_cap_info(rps->caps);
	printk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	for (i = 0; i < ps->num_levels; i++) {
		struct trinity_pl *pl = &ps->levels[i];
		printk("\t\tpower level %d    sclk: %u vddc: %u\n",
		       i, pl->sclk,
		       trinity_convert_voltage_index_to_value(rdev, pl->vddc_index));
	}
	r600_dpm_print_ps_status(rdev, rps);
}