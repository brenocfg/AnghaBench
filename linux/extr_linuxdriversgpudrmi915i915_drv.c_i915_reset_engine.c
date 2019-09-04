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
struct intel_engine_cs {size_t id; int (* init_hw ) (struct intel_engine_cs*) ;int /*<<< orphan*/  name; TYPE_3__* i915; } ;
struct i915_request {int dummy; } ;
struct i915_gpu_error {int /*<<< orphan*/ * reset_engine_count; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ execbuf_client; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_2__ guc; TYPE_1__ drm; struct i915_gpu_error gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ I915_RESET_ENGINE ; 
 scalar_t__ IS_ERR_OR_NULL (struct i915_request*) ; 
 int PTR_ERR (struct i915_request*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  i915_gem_reset_engine (struct intel_engine_cs*,struct i915_request*,int) ; 
 int /*<<< orphan*/  i915_gem_reset_finish_engine (struct intel_engine_cs*) ; 
 struct i915_request* i915_gem_reset_prepare_engine (struct intel_engine_cs*) ; 
 int intel_gt_reset_engine (TYPE_3__*,struct intel_engine_cs*) ; 
 int intel_guc_reset_engine (TYPE_2__*,struct intel_engine_cs*) ; 
 int stub1 (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ *) ; 

int i915_reset_engine(struct intel_engine_cs *engine, const char *msg)
{
	struct i915_gpu_error *error = &engine->i915->gpu_error;
	struct i915_request *active_request;
	int ret;

	GEM_TRACE("%s flags=%lx\n", engine->name, error->flags);
	GEM_BUG_ON(!test_bit(I915_RESET_ENGINE + engine->id, &error->flags));

	active_request = i915_gem_reset_prepare_engine(engine);
	if (IS_ERR_OR_NULL(active_request)) {
		/* Either the previous reset failed, or we pardon the reset. */
		ret = PTR_ERR(active_request);
		goto out;
	}

	if (msg)
		dev_notice(engine->i915->drm.dev,
			   "Resetting %s for %s\n", engine->name, msg);
	error->reset_engine_count[engine->id]++;

	if (!engine->i915->guc.execbuf_client)
		ret = intel_gt_reset_engine(engine->i915, engine);
	else
		ret = intel_guc_reset_engine(&engine->i915->guc, engine);
	if (ret) {
		/* If we fail here, we expect to fallback to a global reset */
		DRM_DEBUG_DRIVER("%sFailed to reset %s, ret=%d\n",
				 engine->i915->guc.execbuf_client ? "GuC " : "",
				 engine->name, ret);
		goto out;
	}

	/*
	 * The request that caused the hang is stuck on elsp, we know the
	 * active request and can drop it, adjust head to skip the offending
	 * request to resume executing remaining requests in the queue.
	 */
	i915_gem_reset_engine(engine, active_request, true);

	/*
	 * The engine and its registers (and workarounds in case of render)
	 * have been reset to their default values. Follow the init_ring
	 * process to program RING_MODE, HWSP and re-enable submission.
	 */
	ret = engine->init_hw(engine);
	if (ret)
		goto out;

out:
	i915_gem_reset_finish_engine(engine);
	return ret;
}