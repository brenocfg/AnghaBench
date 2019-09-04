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
struct amdgpu_job {int /*<<< orphan*/  vm_pd_addr; int /*<<< orphan*/ * ibs; } ;
struct TYPE_2__ {int /*<<< orphan*/  table_addr; } ;
struct amdgpu_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int amdgpu_ib_get (struct amdgpu_device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int amdgpu_job_alloc (struct amdgpu_device*,int,struct amdgpu_job**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_job*) ; 

int amdgpu_job_alloc_with_ib(struct amdgpu_device *adev, unsigned size,
			     struct amdgpu_job **job)
{
	int r;

	r = amdgpu_job_alloc(adev, 1, job, NULL);
	if (r)
		return r;

	r = amdgpu_ib_get(adev, NULL, size, &(*job)->ibs[0]);
	if (r)
		kfree(*job);
	else
		(*job)->vm_pd_addr = adev->gart.table_addr;

	return r;
}