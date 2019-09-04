#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_vm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sched; } ;
struct amdgpu_job {unsigned int num_ibs; int /*<<< orphan*/  vm_pd_addr; int /*<<< orphan*/  vram_lost_counter; int /*<<< orphan*/  sched_sync; int /*<<< orphan*/  sync; void* ibs; struct amdgpu_vm* vm; TYPE_1__ base; } ;
struct amdgpu_ib {int dummy; } ;
struct amdgpu_device {int /*<<< orphan*/  vram_lost_counter; TYPE_2__** rings; } ;
struct TYPE_4__ {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_BO_INVALID_OFFSET ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_sync_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct amdgpu_job* kzalloc (size_t,int /*<<< orphan*/ ) ; 

int amdgpu_job_alloc(struct amdgpu_device *adev, unsigned num_ibs,
		     struct amdgpu_job **job, struct amdgpu_vm *vm)
{
	size_t size = sizeof(struct amdgpu_job);

	if (num_ibs == 0)
		return -EINVAL;

	size += sizeof(struct amdgpu_ib) * num_ibs;

	*job = kzalloc(size, GFP_KERNEL);
	if (!*job)
		return -ENOMEM;

	/*
	 * Initialize the scheduler to at least some ring so that we always
	 * have a pointer to adev.
	 */
	(*job)->base.sched = &adev->rings[0]->sched;
	(*job)->vm = vm;
	(*job)->ibs = (void *)&(*job)[1];
	(*job)->num_ibs = num_ibs;

	amdgpu_sync_create(&(*job)->sync);
	amdgpu_sync_create(&(*job)->sched_sync);
	(*job)->vram_lost_counter = atomic_read(&adev->vram_lost_counter);
	(*job)->vm_pd_addr = AMDGPU_BO_INVALID_OFFSET;

	return 0;
}