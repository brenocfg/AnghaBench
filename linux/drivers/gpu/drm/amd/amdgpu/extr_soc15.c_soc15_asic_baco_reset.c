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
struct TYPE_2__ {struct amd_pm_funcs* pp_funcs; void* pp_handle; } ;
struct amdgpu_device {int in_baco_reset; int /*<<< orphan*/  dev; TYPE_1__ powerplay; } ;
struct amd_pm_funcs {scalar_t__ (* set_asic_baco_state ) (void*,int) ;int /*<<< orphan*/  get_asic_baco_state; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (void*,int) ; 
 scalar_t__ stub2 (void*,int) ; 

__attribute__((used)) static int soc15_asic_baco_reset(struct amdgpu_device *adev)
{
	void *pp_handle = adev->powerplay.pp_handle;
	const struct amd_pm_funcs *pp_funcs = adev->powerplay.pp_funcs;

	if (!pp_funcs ||!pp_funcs->get_asic_baco_state ||!pp_funcs->set_asic_baco_state)
		return -ENOENT;

	/* enter BACO state */
	if (pp_funcs->set_asic_baco_state(pp_handle, 1))
		return -EIO;

	/* exit BACO state */
	if (pp_funcs->set_asic_baco_state(pp_handle, 0))
		return -EIO;

	dev_info(adev->dev, "GPU BACO reset\n");

	adev->in_baco_reset = 1;

	return 0;
}