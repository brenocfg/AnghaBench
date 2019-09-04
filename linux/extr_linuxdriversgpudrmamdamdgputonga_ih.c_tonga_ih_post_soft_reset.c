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
struct TYPE_2__ {int /*<<< orphan*/  srbm_soft_reset; } ;
struct amdgpu_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int tonga_ih_hw_init (struct amdgpu_device*) ; 

__attribute__((used)) static int tonga_ih_post_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (!adev->irq.srbm_soft_reset)
		return 0;

	return tonga_ih_hw_init(adev);
}