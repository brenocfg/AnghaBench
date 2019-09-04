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
struct kv_ps {int num_levels; struct kv_pl* levels; } ;
struct kv_pl {int /*<<< orphan*/  vddc_index; int /*<<< orphan*/  sclk; } ;
struct amdgpu_ps {int /*<<< orphan*/  dclk; int /*<<< orphan*/  vclk; int /*<<< orphan*/  caps; int /*<<< orphan*/  class2; int /*<<< orphan*/  class; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_dpm_print_cap_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dpm_print_class_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dpm_print_ps_status (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  kv_convert_8bit_index_to_voltage (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct kv_ps* kv_get_ps (struct amdgpu_ps*) ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
kv_dpm_print_power_state(void *handle, void *request_ps)
{
	int i;
	struct amdgpu_ps *rps = (struct amdgpu_ps *)request_ps;
	struct kv_ps *ps = kv_get_ps(rps);
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	amdgpu_dpm_print_class_info(rps->class, rps->class2);
	amdgpu_dpm_print_cap_info(rps->caps);
	printk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	for (i = 0; i < ps->num_levels; i++) {
		struct kv_pl *pl = &ps->levels[i];
		printk("\t\tpower level %d    sclk: %u vddc: %u\n",
		       i, pl->sclk,
		       kv_convert_8bit_index_to_voltage(adev, pl->vddc_index));
	}
	amdgpu_dpm_print_ps_status(adev, rps);
}