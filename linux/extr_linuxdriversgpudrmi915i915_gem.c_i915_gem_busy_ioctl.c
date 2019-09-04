#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct reservation_object_list {unsigned int shared_count; int /*<<< orphan*/ * shared; } ;
struct drm_i915_gem_object {TYPE_1__* resv; } ;
struct drm_i915_gem_busy {int /*<<< orphan*/  busy; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  fence; int /*<<< orphan*/  fence_excl; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  busy_check_reader (struct dma_fence*) ; 
 int /*<<< orphan*/  busy_check_writer (void*) ; 
 struct drm_i915_gem_object* i915_gem_object_lookup_rcu (struct drm_file*,int /*<<< orphan*/ ) ; 
 unsigned int raw_read_seqcount (int /*<<< orphan*/ *) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 

int
i915_gem_busy_ioctl(struct drm_device *dev, void *data,
		    struct drm_file *file)
{
	struct drm_i915_gem_busy *args = data;
	struct drm_i915_gem_object *obj;
	struct reservation_object_list *list;
	unsigned int seq;
	int err;

	err = -ENOENT;
	rcu_read_lock();
	obj = i915_gem_object_lookup_rcu(file, args->handle);
	if (!obj)
		goto out;

	/* A discrepancy here is that we do not report the status of
	 * non-i915 fences, i.e. even though we may report the object as idle,
	 * a call to set-domain may still stall waiting for foreign rendering.
	 * This also means that wait-ioctl may report an object as busy,
	 * where busy-ioctl considers it idle.
	 *
	 * We trade the ability to warn of foreign fences to report on which
	 * i915 engines are active for the object.
	 *
	 * Alternatively, we can trade that extra information on read/write
	 * activity with
	 *	args->busy =
	 *		!reservation_object_test_signaled_rcu(obj->resv, true);
	 * to report the overall busyness. This is what the wait-ioctl does.
	 *
	 */
retry:
	seq = raw_read_seqcount(&obj->resv->seq);

	/* Translate the exclusive fence to the READ *and* WRITE engine */
	args->busy = busy_check_writer(rcu_dereference(obj->resv->fence_excl));

	/* Translate shared fences to READ set of engines */
	list = rcu_dereference(obj->resv->fence);
	if (list) {
		unsigned int shared_count = list->shared_count, i;

		for (i = 0; i < shared_count; ++i) {
			struct dma_fence *fence =
				rcu_dereference(list->shared[i]);

			args->busy |= busy_check_reader(fence);
		}
	}

	if (args->busy && read_seqcount_retry(&obj->resv->seq, seq))
		goto retry;

	err = 0;
out:
	rcu_read_unlock();
	return err;
}