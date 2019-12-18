#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ rlc; } ;
struct amdgpu_device {TYPE_3__ gfx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  gfx_v6_0_cp_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v6_0_fini_pg (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v6_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	gfx_v6_0_cp_enable(adev, false);
	adev->gfx.rlc.funcs->stop(adev);
	gfx_v6_0_fini_pg(adev);

	return 0;
}