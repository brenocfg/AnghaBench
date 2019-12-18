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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ num_doorbells; scalar_t__ ptr; } ;
struct amdgpu_device {TYPE_1__ doorbell; } ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 

u64 amdgpu_mm_rdoorbell64(struct amdgpu_device *adev, u32 index)
{
	if (index < adev->doorbell.num_doorbells) {
		return atomic64_read((atomic64_t *)(adev->doorbell.ptr + index));
	} else {
		DRM_ERROR("reading beyond doorbell aperture: 0x%08x!\n", index);
		return 0;
	}
}