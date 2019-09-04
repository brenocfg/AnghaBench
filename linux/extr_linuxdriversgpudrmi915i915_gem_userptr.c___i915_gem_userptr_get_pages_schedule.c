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
struct sg_table {int dummy; } ;
struct get_pages_work {int /*<<< orphan*/  work; int /*<<< orphan*/  task; int /*<<< orphan*/  obj; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * work; } ;
struct drm_i915_gem_object {TYPE_2__ base; TYPE_3__ userptr; } ;
struct TYPE_5__ {int /*<<< orphan*/  userptr_wq; } ;
struct TYPE_8__ {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sg_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_gem_userptr_get_pages_worker ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_get (struct drm_i915_gem_object*) ; 
 struct get_pages_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sg_table *
__i915_gem_userptr_get_pages_schedule(struct drm_i915_gem_object *obj)
{
	struct get_pages_work *work;

	/* Spawn a worker so that we can acquire the
	 * user pages without holding our mutex. Access
	 * to the user pages requires mmap_sem, and we have
	 * a strict lock ordering of mmap_sem, struct_mutex -
	 * we already hold struct_mutex here and so cannot
	 * call gup without encountering a lock inversion.
	 *
	 * Userspace will keep on repeating the operation
	 * (thanks to EAGAIN) until either we hit the fast
	 * path or the worker completes. If the worker is
	 * cancelled or superseded, the task is still run
	 * but the results ignored. (This leads to
	 * complications that we may have a stray object
	 * refcount that we need to be wary of when
	 * checking for existing objects during creation.)
	 * If the worker encounters an error, it reports
	 * that error back to this function through
	 * obj->userptr.work = ERR_PTR.
	 */
	work = kmalloc(sizeof(*work), GFP_KERNEL);
	if (work == NULL)
		return ERR_PTR(-ENOMEM);

	obj->userptr.work = &work->work;

	work->obj = i915_gem_object_get(obj);

	work->task = current;
	get_task_struct(work->task);

	INIT_WORK(&work->work, __i915_gem_userptr_get_pages_worker);
	queue_work(to_i915(obj->base.dev)->mm.userptr_wq, &work->work);

	return ERR_PTR(-EAGAIN);
}