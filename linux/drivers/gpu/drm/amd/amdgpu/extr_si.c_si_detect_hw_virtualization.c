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
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;
struct amdgpu_device {TYPE_1__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PASSTHROUGH_MODE ; 
 scalar_t__ is_virtual_machine () ; 

__attribute__((used)) static void si_detect_hw_virtualization(struct amdgpu_device *adev)
{
	if (is_virtual_machine()) /* passthrough mode */
		adev->virt.caps |= AMDGPU_PASSTHROUGH_MODE;
}