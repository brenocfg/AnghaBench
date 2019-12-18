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
typedef  int u64 ;
struct i915_vma {int fence_size; TYPE_3__* vm; scalar_t__ fence; } ;
struct i915_ggtt_view {scalar_t__ type; } ;
struct i915_address_space {int dummy; } ;
struct TYPE_6__ {int mappable_end; } ;
struct drm_i915_private {TYPE_2__ ggtt; } ;
struct TYPE_5__ {int size; TYPE_4__* dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENODEV ; 
 int ENOSPC ; 
 struct i915_vma* ERR_PTR (int) ; 
 scalar_t__ I915_GGTT_VIEW_NORMAL ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PIN_MAPPABLE ; 
 int PIN_NONBLOCK ; 
 int /*<<< orphan*/  WARN (scalar_t__,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_is_tiled (struct drm_i915_gem_object*) ; 
 scalar_t__ i915_gem_object_never_bind_ggtt (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_ggtt_offset (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct drm_i915_gem_object*,struct i915_address_space*,struct i915_ggtt_view const*) ; 
 scalar_t__ i915_vma_is_active (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_is_map_and_fenceable (struct i915_vma*) ; 
 scalar_t__ i915_vma_is_pinned (struct i915_vma*) ; 
 scalar_t__ i915_vma_misplaced (struct i915_vma*,int,int,int) ; 
 int i915_vma_pin (struct i915_vma*,int,int,int) ; 
 int i915_vma_revoke_fence (struct i915_vma*) ; 
 int i915_vma_unbind (struct i915_vma*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (TYPE_4__*) ; 

struct i915_vma *
i915_gem_object_pin(struct drm_i915_gem_object *obj,
		    struct i915_address_space *vm,
		    const struct i915_ggtt_view *view,
		    u64 size,
		    u64 alignment,
		    u64 flags)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);
	struct i915_vma *vma;
	int ret;

	lockdep_assert_held(&obj->base.dev->struct_mutex);

	if (i915_gem_object_never_bind_ggtt(obj))
		return ERR_PTR(-ENODEV);

	if (flags & PIN_MAPPABLE &&
	    (!view || view->type == I915_GGTT_VIEW_NORMAL)) {
		/* If the required space is larger than the available
		 * aperture, we will not able to find a slot for the
		 * object and unbinding the object now will be in
		 * vain. Worse, doing so may cause us to ping-pong
		 * the object in and out of the Global GTT and
		 * waste a lot of cycles under the mutex.
		 */
		if (obj->base.size > dev_priv->ggtt.mappable_end)
			return ERR_PTR(-E2BIG);

		/* If NONBLOCK is set the caller is optimistically
		 * trying to cache the full object within the mappable
		 * aperture, and *must* have a fallback in place for
		 * situations where we cannot bind the object. We
		 * can be a little more lax here and use the fallback
		 * more often to avoid costly migrations of ourselves
		 * and other objects within the aperture.
		 *
		 * Half-the-aperture is used as a simple heuristic.
		 * More interesting would to do search for a free
		 * block prior to making the commitment to unbind.
		 * That caters for the self-harm case, and with a
		 * little more heuristics (e.g. NOFAULT, NOEVICT)
		 * we could try to minimise harm to others.
		 */
		if (flags & PIN_NONBLOCK &&
		    obj->base.size > dev_priv->ggtt.mappable_end / 2)
			return ERR_PTR(-ENOSPC);
	}

	vma = i915_vma_instance(obj, vm, view);
	if (IS_ERR(vma))
		return vma;

	if (i915_vma_misplaced(vma, size, alignment, flags)) {
		if (flags & PIN_NONBLOCK) {
			if (i915_vma_is_pinned(vma) || i915_vma_is_active(vma))
				return ERR_PTR(-ENOSPC);

			if (flags & PIN_MAPPABLE &&
			    vma->fence_size > dev_priv->ggtt.mappable_end / 2)
				return ERR_PTR(-ENOSPC);
		}

		WARN(i915_vma_is_pinned(vma),
		     "bo is already pinned in ggtt with incorrect alignment:"
		     " offset=%08x, req.alignment=%llx,"
		     " req.map_and_fenceable=%d, vma->map_and_fenceable=%d\n",
		     i915_ggtt_offset(vma), alignment,
		     !!(flags & PIN_MAPPABLE),
		     i915_vma_is_map_and_fenceable(vma));
		ret = i915_vma_unbind(vma);
		if (ret)
			return ERR_PTR(ret);
	}

	if (vma->fence && !i915_gem_object_is_tiled(obj)) {
		mutex_lock(&vma->vm->mutex);
		ret = i915_vma_revoke_fence(vma);
		mutex_unlock(&vma->vm->mutex);
		if (ret)
			return ERR_PTR(ret);
	}

	ret = i915_vma_pin(vma, size, alignment, flags);
	if (ret)
		return ERR_PTR(ret);

	return vma;
}