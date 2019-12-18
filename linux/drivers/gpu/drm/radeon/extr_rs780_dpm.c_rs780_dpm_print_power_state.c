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
struct radeon_ps {int /*<<< orphan*/  dclk; int /*<<< orphan*/  vclk; int /*<<< orphan*/  caps; int /*<<< orphan*/  class2; int /*<<< orphan*/  class; } ;
struct radeon_device {int dummy; } ;
struct igp_ps {int /*<<< orphan*/  max_voltage; int /*<<< orphan*/  sclk_high; int /*<<< orphan*/  min_voltage; int /*<<< orphan*/  sclk_low; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_dpm_print_cap_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_dpm_print_class_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_dpm_print_ps_status (struct radeon_device*,struct radeon_ps*) ; 
 struct igp_ps* rs780_get_ps (struct radeon_ps*) ; 

void rs780_dpm_print_power_state(struct radeon_device *rdev,
				 struct radeon_ps *rps)
{
	struct igp_ps *ps = rs780_get_ps(rps);

	r600_dpm_print_class_info(rps->class, rps->class2);
	r600_dpm_print_cap_info(rps->caps);
	printk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	printk("\t\tpower level 0    sclk: %u vddc_index: %d\n",
	       ps->sclk_low, ps->min_voltage);
	printk("\t\tpower level 1    sclk: %u vddc_index: %d\n",
	       ps->sclk_high, ps->max_voltage);
	r600_dpm_print_ps_status(rdev, rps);
}