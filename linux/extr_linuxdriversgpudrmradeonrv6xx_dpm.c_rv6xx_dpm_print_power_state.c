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
struct rv6xx_pl {int /*<<< orphan*/  vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct rv6xx_ps {struct rv6xx_pl high; struct rv6xx_pl medium; struct rv6xx_pl low; } ;
struct radeon_ps {int /*<<< orphan*/  dclk; int /*<<< orphan*/  vclk; int /*<<< orphan*/  caps; int /*<<< orphan*/  class2; int /*<<< orphan*/  class; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  r600_dpm_print_cap_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_dpm_print_class_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_dpm_print_ps_status (struct radeon_device*,struct radeon_ps*) ; 
 struct rv6xx_ps* rv6xx_get_ps (struct radeon_ps*) ; 

void rv6xx_dpm_print_power_state(struct radeon_device *rdev,
				 struct radeon_ps *rps)
{
	struct rv6xx_ps *ps = rv6xx_get_ps(rps);
	struct rv6xx_pl *pl;

	r600_dpm_print_class_info(rps->class, rps->class2);
	r600_dpm_print_cap_info(rps->caps);
	printk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	pl = &ps->low;
	printk("\t\tpower level 0    sclk: %u mclk: %u vddc: %u\n",
	       pl->sclk, pl->mclk, pl->vddc);
	pl = &ps->medium;
	printk("\t\tpower level 1    sclk: %u mclk: %u vddc: %u\n",
	       pl->sclk, pl->mclk, pl->vddc);
	pl = &ps->high;
	printk("\t\tpower level 2    sclk: %u mclk: %u vddc: %u\n",
	       pl->sclk, pl->mclk, pl->vddc);
	r600_dpm_print_ps_status(rdev, rps);
}