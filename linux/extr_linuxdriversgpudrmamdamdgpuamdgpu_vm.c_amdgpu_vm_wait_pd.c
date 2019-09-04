#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* bo; } ;
struct TYPE_8__ {TYPE_3__ base; } ;
struct amdgpu_vm {TYPE_4__ root; } ;
struct amdgpu_sync {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  resv; } ;
struct TYPE_6__ {TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_sync_create (struct amdgpu_sync*) ; 
 int /*<<< orphan*/  amdgpu_sync_free (struct amdgpu_sync*) ; 
 int /*<<< orphan*/  amdgpu_sync_resv (struct amdgpu_device*,struct amdgpu_sync*,int /*<<< orphan*/ ,void*,int) ; 
 int amdgpu_sync_wait (struct amdgpu_sync*,int) ; 

__attribute__((used)) static int amdgpu_vm_wait_pd(struct amdgpu_device *adev, struct amdgpu_vm *vm,
			     void *owner)
{
	struct amdgpu_sync sync;
	int r;

	amdgpu_sync_create(&sync);
	amdgpu_sync_resv(adev, &sync, vm->root.base.bo->tbo.resv, owner, false);
	r = amdgpu_sync_wait(&sync, true);
	amdgpu_sync_free(&sync);

	return r;
}