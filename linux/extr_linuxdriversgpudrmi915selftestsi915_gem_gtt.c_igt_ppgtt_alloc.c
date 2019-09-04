#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_6__ {int (* allocate_va_range ) (TYPE_2__*,int,int) ;int /*<<< orphan*/  (* clear_range ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  total; } ;
struct i915_hw_ppgtt {TYPE_2__ vm; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct i915_hw_ppgtt*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct i915_hw_ppgtt*) ; 
 int /*<<< orphan*/  USES_PPGTT (struct drm_i915_private*) ; 
 struct i915_hw_ppgtt* __hw_ppgtt_create (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  i915_ppgtt_put (struct i915_hw_ppgtt*) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 
 int stub1 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int stub3 (TYPE_2__*,int,int) ; 
 int totalram_pages ; 

__attribute__((used)) static int igt_ppgtt_alloc(void *arg)
{
	struct drm_i915_private *dev_priv = arg;
	struct i915_hw_ppgtt *ppgtt;
	u64 size, last, limit;
	int err = 0;

	/* Allocate a ppggt and try to fill the entire range */

	if (!USES_PPGTT(dev_priv))
		return 0;

	ppgtt = __hw_ppgtt_create(dev_priv);
	if (IS_ERR(ppgtt))
		return PTR_ERR(ppgtt);

	if (!ppgtt->vm.allocate_va_range)
		goto err_ppgtt_cleanup;

	/*
	 * While we only allocate the page tables here and so we could
	 * address a much larger GTT than we could actually fit into
	 * RAM, a practical limit is the amount of physical pages in the system.
	 * This should ensure that we do not run into the oomkiller during
	 * the test and take down the machine wilfully.
	 */
	limit = totalram_pages << PAGE_SHIFT;
	limit = min(ppgtt->vm.total, limit);

	/* Check we can allocate the entire range */
	for (size = 4096; size <= limit; size <<= 2) {
		err = ppgtt->vm.allocate_va_range(&ppgtt->vm, 0, size);
		if (err) {
			if (err == -ENOMEM) {
				pr_info("[1] Ran out of memory for va_range [0 + %llx] [bit %d]\n",
					size, ilog2(size));
				err = 0; /* virtual space too large! */
			}
			goto err_ppgtt_cleanup;
		}

		cond_resched();

		ppgtt->vm.clear_range(&ppgtt->vm, 0, size);
	}

	/* Check we can incrementally allocate the entire range */
	for (last = 0, size = 4096; size <= limit; last = size, size <<= 2) {
		err = ppgtt->vm.allocate_va_range(&ppgtt->vm,
						  last, size - last);
		if (err) {
			if (err == -ENOMEM) {
				pr_info("[2] Ran out of memory for va_range [%llx + %llx] [bit %d]\n",
					last, size - last, ilog2(size));
				err = 0; /* virtual space too large! */
			}
			goto err_ppgtt_cleanup;
		}

		cond_resched();
	}

err_ppgtt_cleanup:
	mutex_lock(&dev_priv->drm.struct_mutex);
	i915_ppgtt_put(ppgtt);
	mutex_unlock(&dev_priv->drm.struct_mutex);
	return err;
}