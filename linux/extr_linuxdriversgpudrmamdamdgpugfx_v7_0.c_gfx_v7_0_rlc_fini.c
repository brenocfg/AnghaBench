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
struct TYPE_3__ {int /*<<< orphan*/  cp_table_obj; int /*<<< orphan*/  clear_state_obj; int /*<<< orphan*/  save_restore_obj; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_v7_0_rlc_fini(struct amdgpu_device *adev)
{
	amdgpu_bo_free_kernel(&adev->gfx.rlc.save_restore_obj, NULL, NULL);
	amdgpu_bo_free_kernel(&adev->gfx.rlc.clear_state_obj, NULL, NULL);
	amdgpu_bo_free_kernel(&adev->gfx.rlc.cp_table_obj, NULL, NULL);
}