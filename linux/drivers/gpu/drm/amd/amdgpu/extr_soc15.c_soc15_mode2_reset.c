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
struct TYPE_4__ {int /*<<< orphan*/  pp_handle; TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; } ;
struct TYPE_3__ {int (* asic_reset_mode_2 ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc15_mode2_reset(struct amdgpu_device *adev)
{
	if (!adev->powerplay.pp_funcs ||
	    !adev->powerplay.pp_funcs->asic_reset_mode_2)
		return -ENOENT;

	return adev->powerplay.pp_funcs->asic_reset_mode_2(adev->powerplay.pp_handle);
}