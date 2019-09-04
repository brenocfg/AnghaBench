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
struct pp_hwmgr {struct pp_hwmgr* hardcode_pp_table; } ;
struct TYPE_2__ {struct pp_hwmgr* pp_handle; } ;
struct amdgpu_device {TYPE_1__ powerplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pp_hwmgr*) ; 

__attribute__((used)) static void amd_powerplay_destroy(struct amdgpu_device *adev)
{
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	kfree(hwmgr->hardcode_pp_table);
	hwmgr->hardcode_pp_table = NULL;

	kfree(hwmgr);
	hwmgr = NULL;
}