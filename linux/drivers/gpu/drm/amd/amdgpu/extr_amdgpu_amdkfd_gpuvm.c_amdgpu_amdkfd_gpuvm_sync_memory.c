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
struct kgd_mem {int /*<<< orphan*/  lock; int /*<<< orphan*/  sync; } ;
struct kgd_dev {int dummy; } ;
struct amdgpu_sync {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_sync_clone (int /*<<< orphan*/ *,struct amdgpu_sync*) ; 
 int /*<<< orphan*/  amdgpu_sync_create (struct amdgpu_sync*) ; 
 int /*<<< orphan*/  amdgpu_sync_free (struct amdgpu_sync*) ; 
 int amdgpu_sync_wait (struct amdgpu_sync*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int amdgpu_amdkfd_gpuvm_sync_memory(
		struct kgd_dev *kgd, struct kgd_mem *mem, bool intr)
{
	struct amdgpu_sync sync;
	int ret;

	amdgpu_sync_create(&sync);

	mutex_lock(&mem->lock);
	amdgpu_sync_clone(&mem->sync, &sync);
	mutex_unlock(&mem->lock);

	ret = amdgpu_sync_wait(&sync, intr);
	amdgpu_sync_free(&sync);
	return ret;
}