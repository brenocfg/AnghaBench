#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_cs {TYPE_3__* i915; } ;
struct TYPE_6__ {int /*<<< orphan*/  priority; } ;
struct i915_request {TYPE_1__ sched; } ;
struct i915_gem_context {TYPE_1__ sched; } ;
struct drm_file {TYPE_1__ sched; } ;
struct active_engine {int flags; struct intel_engine_cs* engine; } ;
struct TYPE_7__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_8__ {TYPE_2__ drm; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (struct i915_request**) ; 
 int /*<<< orphan*/  I915_RND_STATE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int PTR_ERR (struct i915_request*) ; 
 int TEST_PRIORITY ; 
 int active_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  i915_gem_context_put (struct i915_request*) ; 
 int /*<<< orphan*/  i915_prandom_u32_max_state (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* i915_request_get (struct i915_request*) ; 
 struct i915_request* igt_request_alloc (struct i915_request*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 struct i915_request* live_context (TYPE_3__*,struct i915_request*) ; 
 struct i915_request* mock_file (TYPE_3__*) ; 
 int /*<<< orphan*/  mock_file_free (TYPE_3__*,struct i915_request*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prng ; 

__attribute__((used)) static int active_engine(void *data)
{
	I915_RND_STATE(prng);
	struct active_engine *arg = data;
	struct intel_engine_cs *engine = arg->engine;
	struct i915_request *rq[8] = {};
	struct i915_gem_context *ctx[ARRAY_SIZE(rq)];
	struct drm_file *file;
	unsigned long count = 0;
	int err = 0;

	file = mock_file(engine->i915);
	if (IS_ERR(file))
		return PTR_ERR(file);

	for (count = 0; count < ARRAY_SIZE(ctx); count++) {
		mutex_lock(&engine->i915->drm.struct_mutex);
		ctx[count] = live_context(engine->i915, file);
		mutex_unlock(&engine->i915->drm.struct_mutex);
		if (IS_ERR(ctx[count])) {
			err = PTR_ERR(ctx[count]);
			while (--count)
				i915_gem_context_put(ctx[count]);
			goto err_file;
		}
	}

	while (!kthread_should_stop()) {
		unsigned int idx = count++ & (ARRAY_SIZE(rq) - 1);
		struct i915_request *old = rq[idx];
		struct i915_request *new;

		mutex_lock(&engine->i915->drm.struct_mutex);
		new = igt_request_alloc(ctx[idx], engine);
		if (IS_ERR(new)) {
			mutex_unlock(&engine->i915->drm.struct_mutex);
			err = PTR_ERR(new);
			break;
		}

		if (arg->flags & TEST_PRIORITY)
			ctx[idx]->sched.priority =
				i915_prandom_u32_max_state(512, &prng);

		rq[idx] = i915_request_get(new);
		i915_request_add(new);
		mutex_unlock(&engine->i915->drm.struct_mutex);

		err = active_request_put(old);
		if (err)
			break;

		cond_resched();
	}

	for (count = 0; count < ARRAY_SIZE(rq); count++) {
		int err__ = active_request_put(rq[count]);

		/* Keep the first error */
		if (!err)
			err = err__;
	}

err_file:
	mock_file_free(engine->i915, file);
	return err;
}