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
typedef  struct drm_gem_cma_object* uint32_t ;
struct vc4_exec_info {int bo_count; struct drm_gem_cma_object** bo; struct drm_vc4_submit_cl* args; } ;
struct drm_vc4_submit_cl {int bo_handle_count; int /*<<< orphan*/  bo_handles; } ;
struct drm_gem_object {int dummy; } ;
struct drm_gem_cma_object {int /*<<< orphan*/  base; } ;
struct drm_file {int /*<<< orphan*/  table_lock; int /*<<< orphan*/  object_idr; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 scalar_t__ copy_from_user (struct drm_gem_cma_object**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct drm_gem_object* idr_find (int /*<<< orphan*/ *,struct drm_gem_cma_object*) ; 
 int /*<<< orphan*/  kvfree (struct drm_gem_cma_object**) ; 
 void* kvmalloc_array (int,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_vc4_bo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_bo_dec_usecnt (int /*<<< orphan*/ ) ; 
 int vc4_bo_inc_usecnt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vc4_cl_lookup_bos(struct drm_device *dev,
		  struct drm_file *file_priv,
		  struct vc4_exec_info *exec)
{
	struct drm_vc4_submit_cl *args = exec->args;
	uint32_t *handles;
	int ret = 0;
	int i;

	exec->bo_count = args->bo_handle_count;

	if (!exec->bo_count) {
		/* See comment on bo_index for why we have to check
		 * this.
		 */
		DRM_DEBUG("Rendering requires BOs to validate\n");
		return -EINVAL;
	}

	exec->bo = kvmalloc_array(exec->bo_count,
				    sizeof(struct drm_gem_cma_object *),
				    GFP_KERNEL | __GFP_ZERO);
	if (!exec->bo) {
		DRM_ERROR("Failed to allocate validated BO pointers\n");
		return -ENOMEM;
	}

	handles = kvmalloc_array(exec->bo_count, sizeof(uint32_t), GFP_KERNEL);
	if (!handles) {
		ret = -ENOMEM;
		DRM_ERROR("Failed to allocate incoming GEM handles\n");
		goto fail;
	}

	if (copy_from_user(handles, u64_to_user_ptr(args->bo_handles),
			   exec->bo_count * sizeof(uint32_t))) {
		ret = -EFAULT;
		DRM_ERROR("Failed to copy in GEM handles\n");
		goto fail;
	}

	spin_lock(&file_priv->table_lock);
	for (i = 0; i < exec->bo_count; i++) {
		struct drm_gem_object *bo = idr_find(&file_priv->object_idr,
						     handles[i]);
		if (!bo) {
			DRM_DEBUG("Failed to look up GEM BO %d: %d\n",
				  i, handles[i]);
			ret = -EINVAL;
			break;
		}

		drm_gem_object_get(bo);
		exec->bo[i] = (struct drm_gem_cma_object *)bo;
	}
	spin_unlock(&file_priv->table_lock);

	if (ret)
		goto fail_put_bo;

	for (i = 0; i < exec->bo_count; i++) {
		ret = vc4_bo_inc_usecnt(to_vc4_bo(&exec->bo[i]->base));
		if (ret)
			goto fail_dec_usecnt;
	}

	kvfree(handles);
	return 0;

fail_dec_usecnt:
	/* Decrease usecnt on acquired objects.
	 * We cannot rely on  vc4_complete_exec() to release resources here,
	 * because vc4_complete_exec() has no information about which BO has
	 * had its ->usecnt incremented.
	 * To make things easier we just free everything explicitly and set
	 * exec->bo to NULL so that vc4_complete_exec() skips the 'BO release'
	 * step.
	 */
	for (i-- ; i >= 0; i--)
		vc4_bo_dec_usecnt(to_vc4_bo(&exec->bo[i]->base));

fail_put_bo:
	/* Release any reference to acquired objects. */
	for (i = 0; i < exec->bo_count && exec->bo[i]; i++)
		drm_gem_object_put_unlocked(&exec->bo[i]->base);

fail:
	kvfree(handles);
	kvfree(exec->bo);
	exec->bo = NULL;
	return ret;
}