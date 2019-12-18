#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kgd_mem {int /*<<< orphan*/  lock; int /*<<< orphan*/  sync; struct amdkfd_process_info* process_info; int /*<<< orphan*/  domain; int /*<<< orphan*/  bo; } ;
struct amdkfd_process_info {int /*<<< orphan*/  lock; TYPE_3__* eviction_fence; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct amdgpu_bo {TYPE_2__ tbo; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GWS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_kgd_mem_to_kfd_bo_list (struct kgd_mem*,struct amdkfd_process_info*,int) ; 
 int amdgpu_amdkfd_bo_validate (struct amdgpu_bo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  amdgpu_bo_ref (struct amdgpu_bo*) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_sync_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_sync_free (int /*<<< orphan*/ *) ; 
 int dma_resv_reserve_shared (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct kgd_mem*) ; 
 struct kgd_mem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  remove_kgd_mem_from_kfd_bo_list (struct kgd_mem*,struct amdkfd_process_info*) ; 
 scalar_t__ unlikely (int) ; 

int amdgpu_amdkfd_add_gws_to_process(void *info, void *gws, struct kgd_mem **mem)
{
	struct amdkfd_process_info *process_info = (struct amdkfd_process_info *)info;
	struct amdgpu_bo *gws_bo = (struct amdgpu_bo *)gws;
	int ret;

	if (!info || !gws)
		return -EINVAL;

	*mem = kzalloc(sizeof(struct kgd_mem), GFP_KERNEL);
	if (!*mem)
		return -ENOMEM;

	mutex_init(&(*mem)->lock);
	(*mem)->bo = amdgpu_bo_ref(gws_bo);
	(*mem)->domain = AMDGPU_GEM_DOMAIN_GWS;
	(*mem)->process_info = process_info;
	add_kgd_mem_to_kfd_bo_list(*mem, process_info, false);
	amdgpu_sync_create(&(*mem)->sync);


	/* Validate gws bo the first time it is added to process */
	mutex_lock(&(*mem)->process_info->lock);
	ret = amdgpu_bo_reserve(gws_bo, false);
	if (unlikely(ret)) {
		pr_err("Reserve gws bo failed %d\n", ret);
		goto bo_reservation_failure;
	}

	ret = amdgpu_amdkfd_bo_validate(gws_bo, AMDGPU_GEM_DOMAIN_GWS, true);
	if (ret) {
		pr_err("GWS BO validate failed %d\n", ret);
		goto bo_validation_failure;
	}
	/* GWS resource is shared b/t amdgpu and amdkfd
	 * Add process eviction fence to bo so they can
	 * evict each other.
	 */
	ret = dma_resv_reserve_shared(gws_bo->tbo.base.resv, 1);
	if (ret)
		goto reserve_shared_fail;
	amdgpu_bo_fence(gws_bo, &process_info->eviction_fence->base, true);
	amdgpu_bo_unreserve(gws_bo);
	mutex_unlock(&(*mem)->process_info->lock);

	return ret;

reserve_shared_fail:
bo_validation_failure:
	amdgpu_bo_unreserve(gws_bo);
bo_reservation_failure:
	mutex_unlock(&(*mem)->process_info->lock);
	amdgpu_sync_free(&(*mem)->sync);
	remove_kgd_mem_from_kfd_bo_list(*mem, process_info);
	amdgpu_bo_unref(&gws_bo);
	mutex_destroy(&(*mem)->lock);
	kfree(*mem);
	*mem = NULL;
	return ret;
}