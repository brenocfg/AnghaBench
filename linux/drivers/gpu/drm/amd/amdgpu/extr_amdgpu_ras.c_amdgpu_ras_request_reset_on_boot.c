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
struct amdgpu_ras {int /*<<< orphan*/  flags; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_RAS_FLAG_INIT_NEED_RESET ; 
 int EINVAL ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 

int amdgpu_ras_request_reset_on_boot(struct amdgpu_device *adev,
		unsigned int block)
{
	struct amdgpu_ras *ras = amdgpu_ras_get_context(adev);

	if (!ras)
		return -EINVAL;

	ras->flags |= AMDGPU_RAS_FLAG_INIT_NEED_RESET;
	return 0;
}