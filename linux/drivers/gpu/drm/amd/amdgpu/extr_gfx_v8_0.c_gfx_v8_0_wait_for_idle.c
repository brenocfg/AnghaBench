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
struct amdgpu_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ gfx_v8_0_is_idle (void*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v8_0_wait_for_idle(void *handle)
{
	unsigned int i;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	for (i = 0; i < adev->usec_timeout; i++) {
		if (gfx_v8_0_is_idle(handle))
			return 0;

		udelay(1);
	}
	return -ETIMEDOUT;
}