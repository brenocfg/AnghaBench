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
struct amdgpu_device {int /*<<< orphan*/ * kfd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* device_exit ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* kgd2kfd ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void amdgpu_amdkfd_device_fini(struct amdgpu_device *adev)
{
	if (adev->kfd) {
		kgd2kfd->device_exit(adev->kfd);
		adev->kfd = NULL;
	}
}