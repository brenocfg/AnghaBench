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
struct TYPE_2__ {int /*<<< orphan*/ * pages; } ;
struct amdgpu_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_gart_dummy_page_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void amdgpu_gart_fini(struct amdgpu_device *adev)
{
#ifdef CONFIG_DRM_AMDGPU_GART_DEBUGFS
	vfree(adev->gart.pages);
	adev->gart.pages = NULL;
#endif
	amdgpu_gart_dummy_page_fini(adev);
}