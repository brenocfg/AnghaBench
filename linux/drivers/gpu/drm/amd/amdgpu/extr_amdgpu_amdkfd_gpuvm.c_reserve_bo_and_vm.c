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
struct kgd_mem {int /*<<< orphan*/  sync; struct amdgpu_bo* bo; } ;
struct TYPE_3__ {int num_shared; int /*<<< orphan*/  head; int /*<<< orphan*/ * bo; } ;
struct TYPE_4__ {TYPE_1__ tv; scalar_t__ priority; } ;
struct bo_vm_reservation_context {int reserved; int n_vms; int /*<<< orphan*/ * vm_pd; int /*<<< orphan*/  duplicates; int /*<<< orphan*/  list; int /*<<< orphan*/  ticket; TYPE_2__ kfd_bo; int /*<<< orphan*/ * sync; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_bo {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  amdgpu_vm_get_pd_bo (struct amdgpu_vm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int ttm_eu_reserve_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int reserve_bo_and_vm(struct kgd_mem *mem,
			      struct amdgpu_vm *vm,
			      struct bo_vm_reservation_context *ctx)
{
	struct amdgpu_bo *bo = mem->bo;
	int ret;

	WARN_ON(!vm);

	ctx->reserved = false;
	ctx->n_vms = 1;
	ctx->sync = &mem->sync;

	INIT_LIST_HEAD(&ctx->list);
	INIT_LIST_HEAD(&ctx->duplicates);

	ctx->vm_pd = kcalloc(ctx->n_vms, sizeof(*ctx->vm_pd), GFP_KERNEL);
	if (!ctx->vm_pd)
		return -ENOMEM;

	ctx->kfd_bo.priority = 0;
	ctx->kfd_bo.tv.bo = &bo->tbo;
	ctx->kfd_bo.tv.num_shared = 1;
	list_add(&ctx->kfd_bo.tv.head, &ctx->list);

	amdgpu_vm_get_pd_bo(vm, &ctx->list, &ctx->vm_pd[0]);

	ret = ttm_eu_reserve_buffers(&ctx->ticket, &ctx->list,
				     false, &ctx->duplicates, true);
	if (!ret)
		ctx->reserved = true;
	else {
		pr_err("Failed to reserve buffers in ttm\n");
		kfree(ctx->vm_pd);
		ctx->vm_pd = NULL;
	}

	return ret;
}