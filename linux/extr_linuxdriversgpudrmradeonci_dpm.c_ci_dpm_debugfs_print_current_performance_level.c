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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct radeon_ps {scalar_t__ vce_active; } ;
struct radeon_device {int dummy; } ;
struct ci_power_info {scalar_t__ uvd_enabled; struct radeon_ps current_rps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_get_average_mclk_freq (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_get_average_sclk_freq (struct radeon_device*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 

void ci_dpm_debugfs_print_current_performance_level(struct radeon_device *rdev,
						    struct seq_file *m)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct radeon_ps *rps = &pi->current_rps;
	u32 sclk = ci_get_average_sclk_freq(rdev);
	u32 mclk = ci_get_average_mclk_freq(rdev);

	seq_printf(m, "uvd    %sabled\n", pi->uvd_enabled ? "en" : "dis");
	seq_printf(m, "vce    %sabled\n", rps->vce_active ? "en" : "dis");
	seq_printf(m, "power level avg    sclk: %u mclk: %u\n",
		   sclk, mclk);
}