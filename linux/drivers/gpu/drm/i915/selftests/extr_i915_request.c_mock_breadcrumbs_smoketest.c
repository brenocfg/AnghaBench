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
struct task_struct {int dummy; } ;
struct smoketest {int ncontexts; int max_batch; struct task_struct** contexts; TYPE_2__* engine; int /*<<< orphan*/  num_fences; int /*<<< orphan*/  num_waits; int /*<<< orphan*/  request_alloc; } ;
struct drm_i915_private {TYPE_2__** engine; } ;
struct TYPE_8__ {int /*<<< orphan*/  timeout_jiffies; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_7__ {TYPE_1__ drm; } ;
struct TYPE_6__ {TYPE_3__* i915; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 size_t RCS0 ; 
 int /*<<< orphan*/  __igt_breadcrumbs_smoketest ; 
 int /*<<< orphan*/  __mock_request_alloc ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 TYPE_4__ i915_selftest ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct task_struct**) ; 
 void* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct smoketest*,char*,unsigned int) ; 
 int kthread_stop (struct task_struct*) ; 
 struct task_struct* mock_context (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  mock_context_close (struct task_struct*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int num_online_cpus () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int mock_breadcrumbs_smoketest(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct smoketest t = {
		.engine = i915->engine[RCS0],
		.ncontexts = 1024,
		.max_batch = 1024,
		.request_alloc = __mock_request_alloc
	};
	unsigned int ncpus = num_online_cpus();
	struct task_struct **threads;
	unsigned int n;
	int ret = 0;

	/*
	 * Smoketest our breadcrumb/signal handling for requests across multiple
	 * threads. A very simple test to only catch the most egregious of bugs.
	 * See __igt_breadcrumbs_smoketest();
	 */

	threads = kmalloc_array(ncpus, sizeof(*threads), GFP_KERNEL);
	if (!threads)
		return -ENOMEM;

	t.contexts =
		kmalloc_array(t.ncontexts, sizeof(*t.contexts), GFP_KERNEL);
	if (!t.contexts) {
		ret = -ENOMEM;
		goto out_threads;
	}

	mutex_lock(&t.engine->i915->drm.struct_mutex);
	for (n = 0; n < t.ncontexts; n++) {
		t.contexts[n] = mock_context(t.engine->i915, "mock");
		if (!t.contexts[n]) {
			ret = -ENOMEM;
			goto out_contexts;
		}
	}
	mutex_unlock(&t.engine->i915->drm.struct_mutex);

	for (n = 0; n < ncpus; n++) {
		threads[n] = kthread_run(__igt_breadcrumbs_smoketest,
					 &t, "igt/%d", n);
		if (IS_ERR(threads[n])) {
			ret = PTR_ERR(threads[n]);
			ncpus = n;
			break;
		}

		get_task_struct(threads[n]);
	}

	msleep(jiffies_to_msecs(i915_selftest.timeout_jiffies));

	for (n = 0; n < ncpus; n++) {
		int err;

		err = kthread_stop(threads[n]);
		if (err < 0 && !ret)
			ret = err;

		put_task_struct(threads[n]);
	}
	pr_info("Completed %lu waits for %lu fence across %d cpus\n",
		atomic_long_read(&t.num_waits),
		atomic_long_read(&t.num_fences),
		ncpus);

	mutex_lock(&t.engine->i915->drm.struct_mutex);
out_contexts:
	for (n = 0; n < t.ncontexts; n++) {
		if (!t.contexts[n])
			break;
		mock_context_close(t.contexts[n]);
	}
	mutex_unlock(&t.engine->i915->drm.struct_mutex);
	kfree(t.contexts);
out_threads:
	kfree(threads);

	return ret;
}