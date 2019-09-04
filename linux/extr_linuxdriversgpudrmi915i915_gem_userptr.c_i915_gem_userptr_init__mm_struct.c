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
struct i915_mm_struct {int /*<<< orphan*/  kref; scalar_t__ mm; int /*<<< orphan*/  node; int /*<<< orphan*/ * mn; void* i915; } ;
struct drm_i915_private {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  mm_structs; } ;
struct TYPE_5__ {struct i915_mm_struct* mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_2__ userptr; TYPE_1__ base; } ;
struct TYPE_6__ {scalar_t__ mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct i915_mm_struct* __i915_mm_struct_find (struct drm_i915_private*,scalar_t__) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 struct i915_mm_struct* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmgrab (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i915_gem_userptr_init__mm_struct(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);
	struct i915_mm_struct *mm;
	int ret = 0;

	/* During release of the GEM object we hold the struct_mutex. This
	 * precludes us from calling mmput() at that time as that may be
	 * the last reference and so call exit_mmap(). exit_mmap() will
	 * attempt to reap the vma, and if we were holding a GTT mmap
	 * would then call drm_gem_vm_close() and attempt to reacquire
	 * the struct mutex. So in order to avoid that recursion, we have
	 * to defer releasing the mm reference until after we drop the
	 * struct_mutex, i.e. we need to schedule a worker to do the clean
	 * up.
	 */
	mutex_lock(&dev_priv->mm_lock);
	mm = __i915_mm_struct_find(dev_priv, current->mm);
	if (mm == NULL) {
		mm = kmalloc(sizeof(*mm), GFP_KERNEL);
		if (mm == NULL) {
			ret = -ENOMEM;
			goto out;
		}

		kref_init(&mm->kref);
		mm->i915 = to_i915(obj->base.dev);

		mm->mm = current->mm;
		mmgrab(current->mm);

		mm->mn = NULL;

		/* Protected by dev_priv->mm_lock */
		hash_add(dev_priv->mm_structs,
			 &mm->node, (unsigned long)mm->mm);
	} else
		kref_get(&mm->kref);

	obj->userptr.mm = mm;
out:
	mutex_unlock(&dev_priv->mm_lock);
	return ret;
}