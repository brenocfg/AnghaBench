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
struct TYPE_2__ {int /*<<< orphan*/  va; int /*<<< orphan*/  reserved_bo; } ;
struct amdgpu_device {TYPE_1__ fw_vram_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_ttm_fw_reserve_vram_fini(struct amdgpu_device *adev)
{
	amdgpu_bo_free_kernel(&adev->fw_vram_usage.reserved_bo,
		NULL, &adev->fw_vram_usage.va);
}