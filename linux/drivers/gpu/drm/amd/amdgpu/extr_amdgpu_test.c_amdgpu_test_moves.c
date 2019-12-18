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
struct TYPE_2__ {scalar_t__ buffer_funcs; } ;
struct amdgpu_device {TYPE_1__ mman; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_do_test_moves (struct amdgpu_device*) ; 

void amdgpu_test_moves(struct amdgpu_device *adev)
{
	if (adev->mman.buffer_funcs)
		amdgpu_do_test_moves(adev);
}