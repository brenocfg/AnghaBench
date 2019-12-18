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
struct TYPE_2__ {int /*<<< orphan*/ * bo; } ;
struct amdgpu_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_unref (int /*<<< orphan*/ **) ; 

void amdgpu_gart_table_vram_free(struct amdgpu_device *adev)
{
	if (adev->gart.bo == NULL) {
		return;
	}
	amdgpu_bo_unref(&adev->gart.bo);
}