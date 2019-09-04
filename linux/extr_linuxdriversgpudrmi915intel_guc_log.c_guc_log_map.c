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
struct TYPE_6__ {void* buf_addr; int /*<<< orphan*/  lock; } ;
struct intel_guc_log {TYPE_3__ relay; TYPE_2__* vma; } ;
struct intel_guc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct TYPE_5__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  I915_MAP_WC ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 void* i915_gem_object_pin_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_wc_domain (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct intel_guc* log_to_guc (struct intel_guc_log*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int guc_log_map(struct intel_guc_log *log)
{
	struct intel_guc *guc = log_to_guc(log);
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	void *vaddr;
	int ret;

	lockdep_assert_held(&log->relay.lock);

	if (!log->vma)
		return -ENODEV;

	mutex_lock(&dev_priv->drm.struct_mutex);
	ret = i915_gem_object_set_to_wc_domain(log->vma->obj, true);
	mutex_unlock(&dev_priv->drm.struct_mutex);
	if (ret)
		return ret;

	/*
	 * Create a WC (Uncached for read) vmalloc mapping of log
	 * buffer pages, so that we can directly get the data
	 * (up-to-date) from memory.
	 */
	vaddr = i915_gem_object_pin_map(log->vma->obj, I915_MAP_WC);
	if (IS_ERR(vaddr)) {
		DRM_ERROR("Couldn't map log buffer pages %d\n", ret);
		return PTR_ERR(vaddr);
	}

	log->relay.buf_addr = vaddr;

	return 0;
}