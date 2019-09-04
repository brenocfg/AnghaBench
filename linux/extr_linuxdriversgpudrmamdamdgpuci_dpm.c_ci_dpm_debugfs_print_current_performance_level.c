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
struct seq_file {int dummy; } ;
struct amdgpu_ps {scalar_t__ vce_active; } ;
struct ci_power_info {scalar_t__ uvd_power_gated; struct amdgpu_ps current_rps; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AverageGraphicsA ; 
 int /*<<< orphan*/  SMU7_SoftRegisters ; 
 int ci_get_average_mclk_freq (struct amdgpu_device*) ; 
 int ci_get_average_sclk_freq (struct amdgpu_device*) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int ci_read_smc_soft_register (struct amdgpu_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void
ci_dpm_debugfs_print_current_performance_level(void *handle,
					       struct seq_file *m)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);
	struct amdgpu_ps *rps = &pi->current_rps;
	u32 sclk = ci_get_average_sclk_freq(adev);
	u32 mclk = ci_get_average_mclk_freq(adev);
	u32 activity_percent = 50;
	int ret;

	ret = ci_read_smc_soft_register(adev, offsetof(SMU7_SoftRegisters, AverageGraphicsA),
					&activity_percent);

	if (ret == 0) {
		activity_percent += 0x80;
		activity_percent >>= 8;
		activity_percent = activity_percent > 100 ? 100 : activity_percent;
	}

	seq_printf(m, "uvd %sabled\n", pi->uvd_power_gated ? "dis" : "en");
	seq_printf(m, "vce %sabled\n", rps->vce_active ? "en" : "dis");
	seq_printf(m, "power level avg    sclk: %u mclk: %u\n",
		   sclk, mclk);
	seq_printf(m, "GPU load: %u %%\n", activity_percent);
}