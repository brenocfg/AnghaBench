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
struct pp_hwmgr {int dummy; } ;
struct TYPE_2__ {struct pp_hwmgr* pp_handle; } ;
struct amdgpu_device {TYPE_1__ powerplay; } ;

/* Variables and functions */
 int hwmgr_sw_init (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 

__attribute__((used)) static int pp_sw_init(void *handle)
{
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;
	int ret = 0;

	ret = hwmgr_sw_init(hwmgr);

	pr_debug("powerplay sw init %s\n", ret ? "failed" : "successfully");

	return ret;
}