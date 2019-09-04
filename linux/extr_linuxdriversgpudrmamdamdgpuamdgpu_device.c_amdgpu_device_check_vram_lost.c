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
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;
struct amdgpu_device {int /*<<< orphan*/  reset_magic; TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_RESET_MAGIC_NUM ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool amdgpu_device_check_vram_lost(struct amdgpu_device *adev)
{
	return !!memcmp(adev->gart.ptr, adev->reset_magic,
			AMDGPU_RESET_MAGIC_NUM);
}