#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int vi_common_hw_init (struct amdgpu_device*) ; 

__attribute__((used)) static int vi_common_resume(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	return vi_common_hw_init(adev);
}