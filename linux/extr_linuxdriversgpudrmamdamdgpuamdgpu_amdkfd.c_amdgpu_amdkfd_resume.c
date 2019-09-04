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
struct amdgpu_device {scalar_t__ kfd; } ;
struct TYPE_2__ {int (* resume ) (scalar_t__) ;} ;

/* Variables and functions */
 TYPE_1__* kgd2kfd ; 
 int stub1 (scalar_t__) ; 

int amdgpu_amdkfd_resume(struct amdgpu_device *adev)
{
	int r = 0;

	if (adev->kfd)
		r = kgd2kfd->resume(adev->kfd);

	return r;
}